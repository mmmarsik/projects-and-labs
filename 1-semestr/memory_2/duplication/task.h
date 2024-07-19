#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

std::vector<std::shared_ptr<std::string>> DeDuplicate(const std::vector<std::unique_ptr<std::string>>& in) {
    std::vector<std::shared_ptr<std::string>> out(in.size());
    std::unordered_map<std::string, std::shared_ptr<std::string>> storage;
    for (std::size_t i = 0; i < in.size(); ++i) {
        // если еще не создавал
        if (storage.find(*in[i]) == storage.end()){
            storage[*in[i]] = std::make_shared<std::string>(*in[i]);
        }// если уже есть, то if не сработает и просто заполнил ячейку out[i]
        out[i] = storage[*in[i]];
    }
    return out;
}

std::vector<std::unique_ptr<std::string>> Duplicate(const std::vector<std::shared_ptr<std::string>>& in) {
    // все переменные становятся уникальными
    std::vector<std::unique_ptr<std::string>> out(in.size());
    for (std::size_t i = 0; i < in.size(); ++i) {
        out[i] = std::make_unique<std::string>(*in[i]);
    }
    return out;
}