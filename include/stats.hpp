#pragma once

#include <eosio/eosio.hpp>
#include <eosio/time.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/singleton.hpp>
#include <eosio/asset.hpp>

using namespace eosio;
using std::vector;
using std::string;

#include <voter_info.hpp>

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
                _global( _self, _self.value ),
                _voters( "eosio"_n, "eosio"_n.value )
        {}

        /**
         * Update statistics
         */
        [[eosio::action]] void update(
            uint32_t limit
        );

        [[eosio::action]] void remove();

    private:
        /**
         * Final Statistics table
         */
        struct [[eosio::table]] global {
            time_point_sec  modified_at = current_time_point();
            int64_t         voters_staked = 0;
            int64_t         voters_staked_producers = 0;
            int64_t         voters_staked_proxy = 0;

            uint64_t primary_key() const { return 0; }
        };

        // /**
        //  * Statistics table
        //  */
        // struct [[eosio::table]] progress {
        //     time_point_sec  modified_at = current_time_point();
        //     int64_t         staked = 0;
        //     uint32_t        vote_count = 0;
        //     name            last_owner;

        //     uint64_t primary_key() const { return 0; }
        // };

        typedef eosio::singleton<"global"_n, global> global_table;
        typedef eosio::multi_index<"voters"_n, voter_info> voter_table;

        // local instances of the multi indexes
        global_table            _global;
        voter_table             _voters;
};