#include "task.h"

bool operator <(const SuperKey& lhs, const SuperKey& rhs) {
    if (lhs.StrPart ==  rhs.StrPart ){
        if (lhs.IntPart == rhs.IntPart) return lhs.FloatPart < rhs.FloatPart;
        return lhs.IntPart < rhs.IntPart;
    }
    return lhs.StrPart < rhs.StrPart;
}

void PopulateMap(
    std::map<SuperKey, std::string>& map,
    const std::vector<std::pair<SuperKey, std::string>>& toAdd
) {
    for (auto& x :toAdd){
        map.insert(x);
    }
}
