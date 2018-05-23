//
// Created by root on 01/05/18.
//

#ifndef CMINER_LRUCACHE_H
#define CMINER_LRUCACHE_H


#include <unordered_map>
#include <list>
#include <cstddef>
#include <stdexcept>
#include <mutex>
#include <string>


#ifdef __cplusplus
extern "C" {
#endif

namespace cache {

    class LRUCache {

    public:
        typedef typename std::pair<std::string, std::string> key_value_pair_t;
        typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

        LRUCache(size_t max_size) :
                _max_size(max_size) {
        }

        void put(const std::string &key, const std::string &value) {
            mt.lock();
            auto it = _cache_items_map.find(key);
            _cache_items_list.push_front(key_value_pair_t(key, value));
            if (it != _cache_items_map.end()) {
                _cache_items_list.erase(it->second);
                _cache_items_map.erase(it);
            }
            _cache_items_map[key] = _cache_items_list.begin();

            if (_cache_items_map.size() > _max_size) {
                auto last = _cache_items_list.end();
                last--;
                _cache_items_map.erase(last->first);
                _cache_items_list.pop_back();
            }
            mt.unlock();
        }

        const std::string &get(const std::string &key) {
            mt.lock();
            auto it = _cache_items_map.find(key);
            if (it == _cache_items_map.end()) {
                mt.unlock();
                throw std::range_error("There is no such key in cache");
            } else {
                _cache_items_list.splice(_cache_items_list.begin(), _cache_items_list, it->second);
                mt.unlock();
                return it->second->second;
            }

        }

        bool exists(const std::string &key) const {
            return _cache_items_map.find(key) != _cache_items_map.end();
        }

        size_t size() const {
            return _cache_items_map.size();
        }

    private:
        std::list<key_value_pair_t> _cache_items_list;
        std::unordered_map<std::string, list_iterator_t> _cache_items_map;
        size_t _max_size;

        std::mutex mt;

    };

} // namespace cache

void put(char *k, char *v);
void get(char *k, char *v);

#ifdef __cplusplus
}
#endif

#endif //CMINER_LRUCACHE_H
