#include <eosio/eosio.hpp>
#include <eosio/time.hpp>
#include <eosio/system.hpp>
#include <eosio/singleton.hpp>

#include <string>
#include <optional>

using eosio::check;
using eosio::current_time_point;
using eosio::time_point_sec;
using eosio::name;
using eosio::print;

using std::vector;
using std::string;
using std::optional;

class [[eosio::contract("stats")]] stats : public eosio::contract {
    public:
        /**
         * Construct a new contract given the contract name
         *
         * @param {name} receiver - The name of this contract
         * @param {name} code - The code name of the action this contract is processing.
         * @param {datastream} ds - The datastream used
         */
        stats( name receiver, name code, eosio::datastream<const char*> ds )
            : contract( receiver, code, ds ),
                _global( _self, _self.value )
        {}

        /**
         * Update statistics
         */
        [[eosio::action]] void update();

    private:
        /**
         * Statistics table
         */
        struct [[eosio::table]] global_row {
            time_point_sec  modified_at;

            uint64_t primary_key() const { return 0; }
        };

        typedef eosio::singleton<"global"_n, global_row> global_table;

        // local instances of the multi indexes
        global_table        _global;
};