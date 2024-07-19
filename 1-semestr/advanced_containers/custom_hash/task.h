#include <unordered_map>
#include <vector>
#include <string>

struct SuperKey {
    std::string StrPart;
    int IntPart;
    float FloatPart;

    bool operator==(const SuperKey& rhs) const {
        return this->StrPart == rhs.StrPart && this->IntPart == rhs.IntPart && this->FloatPart == rhs.FloatPart;
    }
};

namespace std{
    template<>
    struct hash<SuperKey>{
        size_t operator()(const SuperKey& s_key) const{
            size_t h1 = hash<string>()(s_key.StrPart);
            size_t h2 = hash<int>()(s_key.IntPart);
            size_t h3 = hash<float>()(s_key.FloatPart);
            return (h1 ^ h2 ^ h3);
        }
    };
}

void PopulateHashMap(
    std::unordered_map<SuperKey, std::string>& hashMap,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
);

