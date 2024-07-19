#include <chrono>
#include <sstream>

class Timer {
public:
    Timer(std::chrono::duration<double> period_)
            : period(period_) {
        start = std::chrono::steady_clock::now();
    }

    bool Expired() const {
        std::chrono::time_point <std::chrono::steady_clock> end = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_from_start = end - start;
        if (time_from_start < period) {
            return false;
        }
        return true;
    }


private:
    std::chrono::duration<double> period;
    std::chrono::time_point <std::chrono::steady_clock> start;
};

class TimeMeasurer {
public:
    TimeMeasurer(std::ostream &stream_)
            : my_stream(stream_) {
        start = std::chrono::steady_clock::now();
    }

    ~TimeMeasurer() {

        std::chrono::time_point <std::chrono::steady_clock> stop = std::chrono::steady_clock::now();
        auto proshlo = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        my_stream << "Elapsed time: " << proshlo.count() << std::endl;
    }

private:
    std::ostream& my_stream;
    std::chrono::time_point <std::chrono::steady_clock> start;
};
