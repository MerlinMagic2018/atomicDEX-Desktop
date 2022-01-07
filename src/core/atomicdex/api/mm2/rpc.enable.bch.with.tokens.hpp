#pragma once

#include "atomicdex/config/electrum.cfg.hpp"
#include "format.address.hpp"
#include "utxo.merge.params.hpp"

namespace mm2::api
{
    struct slp_token_request
    {
        std::string ticker;
        std::optional<std::size_t> required_confirmations;
    };

    void to_json(nlohmann::json& j, const slp_token_request& cfg);

    struct enable_rpc_data
    {
        std::vector<atomic_dex::electrum_server> servers;
    };

    struct enable_mode
    {
        // Native or Electrum
        std::string rpc{"Electrum"};

        enable_rpc_data rpc_data;
    };
    //! Only for erc 20
    struct enable_bch_with_tokens
    {
        // string, mandatory. Ticker of the platform BCH protocol coin.
        std::string ticker;

        // bool, optional. If "true", allows bchd_urls to be empty.
        // Please mark that it is highly unsafe to do so as it may lead to invalid SLP transactions generation and following tokens burn.
        // Defaults to "false".
        std::optional<bool> allow_slp_unsafe_conf{std::nullopt};

        // an array of strings, mandatory. URLs of BCHD gRPC API servers that are used for SLP tokens transactions validation.
        // It's recommended to add as many servers as possible.
        // The URLs list can be found at https://bchd.fountainhead.cash/
        std::vector<std::string> bchd_urls;

        // Utxo RPC mode, mandatory. Value for native: { "rpc":"Native" }
        enable_mode mode;

        // bool, optional. Whether to enable tx history - if "true", spawns a background loop to store the local cache of address(es) transactions.
        // Defaults to "false".
        bool tx_history{true};

        // Array of SLP activation requests, mandatory. SLP activation requests contain mandatory ticker and optional required_confirmations fields.
        // If required_confirmations is not set for a token, then MM2 will use the confirmations setting from its coins config or platform coin.
        std::vector<slp_token_request> slp_token_requests;

        // Number (unsigned integer), optional. The value from the coins file will be used if not set.
        std::optional<std::size_t> required_confirmations;

        // bool, optional. Has no effect on BCH. Defaults to "false".
        std::optional<bool> requires_notarization;

        // address format, optional. Overwrites the address format from coins file, if set.
        // Value to use legacy/standard address format: { "format":"standard" }
        std::optional<format_address> address_format;

        // utxo merge params, optional.
        // If set spawns a background loop that checks the number of UTXOs every check_every seconds,
        // and merges max_merge_at_once to one if the total exceeds merge_at.
        // Useful for active traders as every swap leads to a new UTXO to occur on the address.
        std::optional<utxo_merge_params> utxo_merge_params;
    };
}