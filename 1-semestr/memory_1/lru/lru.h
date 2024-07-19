#include <unordered_map>
#include <queue>

using namespace std;

template<typename K, typename V>
class LruCache {
public:
    LruCache(size_t max_size_) : max_size(max_size_) {}

    void Put(const K &key, const V &value) {
        if (my_un_map.find(key) != my_un_map.end()){
            my_un_map[key] = value;
            push_list.push(key);
            ++elems_cnt[key];
        } else{
            if (local_size_cnt >= max_size){
                while (!(push_list.empty()) && elems_cnt[push_list.front()] > 1){
                    --elems_cnt[push_list.front()];
                    push_list.pop();
                }
                my_un_map.erase(push_list.front());
                elems_cnt.erase(push_list.front());
                push_list.pop();
                --local_size_cnt;
            }
            my_un_map[key] = value;
            push_list.push(key);
            ++local_size_cnt;
            elems_cnt[key] = 1;
        }
    }

    bool Get(const K &key, V *value) {
        if (my_un_map.find(key) == my_un_map.end()){
            return false;
        }
        *value = my_un_map[key];
        push_list.push(key);
        ++elems_cnt[key];
        return true;
    }
private:
    std::size_t max_size;
    std::size_t local_size_cnt = 0;
    std::unordered_map<K, V> my_un_map;
    std::unordered_map<K, size_t> elems_cnt;
    std::queue<K> push_list;
};
