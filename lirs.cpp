#include <iostream>
#include <list>
#include <unordered_map>

enum Status {
    HIR = 0,
    LIR,
    NON_RES_HIR,
};

class CacheElem {
        int key;
        Status status;
    public:
        CacheElem(int num) {key = num;}
        void status_change(Status stat) {status = stat;}
        Status get_status() {return status;}
        int get_key() {return key;}
};

class Cache {
        size_t cache_size;
        size_t lirs_size;
        size_t hirs_size;
    public:
        std::list<class CacheElem> queue;
        std::list<class CacheElem> hirs;
        std::unordered_map<int, std::list<class CacheElem>::iterator> hash;

        Cache(size_t m) { 
            cache_size = m; 
            lirs_size = m * 0.99;
            hirs_size = m - lirs_size;
        }
        size_t get_lirs_size() { return lirs_size; }
        size_t get_hirs_size() { return hirs_size; }

        void purning() {
            auto it = queue.end();
            it--;

            while(it->get_status() != LIR && it != queue.begin()) {
                it--;
                queue.pop_back();
            }
        }

        void up_elem(std::__cxx11::list<CacheElem>::iterator it) {
            queue.splice(queue.begin(), queue, it);

            if((queue.end()--)->get_status() != LIR) {
                purning();
            }
        }

        void delete_last_hir() {
            if(hash.find(hirs.back().get_key()) != hash.end()) { 
                        hash.find(hirs.back().get_key())->second->status_change(NON_RES_HIR);
                }
                hirs.pop_back();
        }
};

int main() {
    size_t m = 0;
    int n = 0;
    int key = 0;

    std::pair<int, std::list<class CacheElem>::iterator> val;

    std::cin>>m>>n;

    Cache LirsCache(m);

    for(size_t i = 0; i < n; i++) {
        
        std::cin>>key;

        //std::cout<<"["<<key<<"["<<std::endl;

        auto it_found = LirsCache.hash.find(key);

        if(it_found == LirsCache.hash.end()) { //there is no such element in the cache
            CacheElem NewElem(key);
            LirsCache.queue.push_front(NewElem);
            if(LirsCache.queue.size() < LirsCache.get_lirs_size()) {
                //std::cout<<"{"<<key<<"}"<<std::endl;
                NewElem.status_change(LIR);
                //std::cout<<"{"<<NewElem.get_status()<<"}"<<std::endl;
            }
            else {
                //std::cout<<"["<<key<<"]"<<std::endl;
                NewElem.status_change(HIR);
                //std::cout<<"["<<key<<"]"<<std::endl;
                LirsCache.hirs.push_front(NewElem);
                if(LirsCache.hirs.size() > LirsCache.get_hirs_size()) {
                    LirsCache.delete_last_hir();
                }
            }
            val = make_pair(key, LirsCache.queue.begin());
            LirsCache.hash.insert(val);
            //std::cout<<"!"<<LirsCache.queue.begin()->get_key()<<"!"<<std::endl;
        }
        else if(it_found->second->get_status() == LIR) {
            LirsCache.up_elem(it_found->second);
            //auto it = it_found->second;
        }
        // LirsCache.purning();
        std::cout<<"----------------------"<<std::endl;
        for(auto itt = LirsCache.queue.begin(); itt != LirsCache.queue.end(); ++itt) {
            std::cout<<itt->get_key()<<" "<<itt->get_status()<<" "<<std::endl;
        }
        std::cout<<"----------------------"<<std::endl;
    }

    for(auto it = LirsCache.queue.begin(); it != LirsCache.queue.end(); ++it) {
        std::cout<<it->get_key()<<" "<<it->get_status()<<" "<<std::endl;
    }

    //std::cout<<LirsCache.hash.find(1)->second->get_status()<<std::endl;

    //std::cout<<"AAAAAAAAAAAA"<<std::endl;

    //LirsCache.purning();

    /* for(auto it = LirsCache.queue.begin(); it != LirsCache.queue.end(); ++it) {
        std::cout<<it->get_key()<<std::endl;
    } */

    //std::cout<<LirsCache.get_param()<<std::endl;

    return 0;
}