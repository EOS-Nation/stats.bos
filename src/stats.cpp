#include "stats.hpp"

void stats::update(uint32_t limit) {

    auto global = _global.get_or_create(_self);

    uint32_t vote_count = 0;
    int64_t staked = 0;
    name last_owner = global.last_owner;

    // Find all cases of delegated bandwidth and sum them up
    auto voters = _voters.find(last_owner.value);

    while (voters != _voters.end()) {
        staked += voters->staked;
        last_owner = voters->owner;
        vote_count += 1;
        voters++;
        if (vote_count >= limit) break;
    }

    global.modified_at = current_time_point();
    global.staked = staked;
    global.vote_count = vote_count;
    global.last_owner = last_owner;

    // Add `properties` table
    _global.set(global, _self);
}

void stats::remove() {
    _global.remove();
}
