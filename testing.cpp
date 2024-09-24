#include <iostream>
#include <list>
#include <unordered_map>

enum status {
    HIR,
    LIR,
    NON_RESIDENT,
};

const size_t INF = 10000;

class Cache {
        size_t cache_size;
    public:
        Cache(size_t m) { cache_size = m; }

        size_t max_r_lirs;
        size_t min_irr_hirs;

        std::list<class CacheElem>::iterator it_max_r_lirs;
        std::list<class CacheElem>::iterator it_min_irr_hirs;

        std::list<int>::iterator lirs;
        std::list<int>::iterator hirs;
};

class CacheElem {
        int key;
    public:
        CacheElem(int num) { key = num; }
        size_t R;
        size_t IRR;
        status stat;
        std::list<int>::iterator cache_block;
};

int main() {

    size_t m = 0;
    int n = 0;
    int key = 0;
    int hits = 0;

    //struct Cache LirsCache = {};

    std::list<class CacheElem> queue;
    std::list<class CacheElem> hirs;
    std::unordered_map<int, std::list<class CacheElem>::iterator> hash;
    std::pair<int, std::list<class CacheElem>::iterator> val;

    std::cin>>m>>n;

    Cache LirsCache(m);

    for(size_t i = 0; i < n; i++) {
        std::cin>>key;
        for(auto it = queue.begin(); it != queue.end(); ++it) {
            it->R++;
            if(it->stat == LIR && LirsCache.max_r_lirs < it->R) {
                LirsCache.max_r_lirs = it->R;
                LirsCache.it_max_r_lirs = it;
            }
            if(it->stat == HIR && LirsCache.min_irr_hirs > it->IRR) {
                LirsCache.min_irr_hirs = it->IRR;
                LirsCache.it_min_irr_hirs = it;
            }
        }
        if(LirsCache.max_r_lirs > LirsCache.min_irr_hirs) {
            //splice
        }
        try {
            auto it_elem = hash.at(key);
            it_elem->IRR = it_elem->R;
            it_elem->R = 0;
            //hirs.splice(hirs.begin(), hirs, hash.at(key));
            hits++;
        }
        catch(std::out_of_range) {
            CacheElem cache_elem(key);
            cache_elem.IRR = INF;
            queue.push_front(cache_elem);
            if(hirs.size() > m) {
                hash.erase(hirs.back());
                hirs.pop_back();
            }
            val = make_pair(key, queue.begin());
            hash.insert(val);
        }
    }

    std::cout<<hits<<std::endl;

    return 0;
}
