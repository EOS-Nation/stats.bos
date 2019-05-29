#include "stats.hpp"

void stats::update() {
    time_point_sec timestamp = current_time_point();

    auto global = _global.get();
    global.modified_at = timestamp;

    // Add `properties` table
    _global.set(global, _self);
}
