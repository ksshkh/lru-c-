#include <iostream>
#include <list>
#include <unordered_map>

int main() {

    size_t m = 0;
    int n = 0;
    int key = 0;
    int hits = 0;

    std::list<int> lst;
    std::unordered_map<int, std::list<int>::iterator> hash;
    std::pair<int, std::list<int>::iterator> val;

    std::cin>>m>>n;

    for(size_t i = 0; i < n; i++) {
        std::cin>>key;
        try {
            hash.at(key);
            lst.splice(lst.begin(), lst, hash.at(key));
            hits++;
        }
        catch(std::out_of_range) {
            lst.push_front(key);
            if(lst.size() > m) {
                hash.erase(lst.back());
                lst.pop_back();
            }
            val = make_pair(key, lst.begin());
            hash.insert(val);
        }
    }

    std::cout<<hits<<std::endl;

    return 0;
}