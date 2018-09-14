#pragma once

#include <eosio/http_plugin/http_plugin.hpp>
#include <eosio/chain_plugin/chain_plugin.hpp>

#include <appbase/application.hpp>

namespace eosio {

using namespace appbase;

class all_code_dump_plugin : public plugin<all_code_dump_plugin> {
public:
   APPBASE_PLUGIN_REQUIRES((http_plugin) (chain_plugin))

   all_code_dump_plugin() = default;
   all_code_dump_plugin(const all_code_dump_plugin&) = delete;
   all_code_dump_plugin(all_code_dump_plugin&&) = delete;
   all_code_dump_plugin& operator=(const all_code_dump_plugin&) = delete;
   all_code_dump_plugin& operator=(all_code_dump_plugin&&) = delete;
   virtual ~all_code_dump_plugin() override = default;

   virtual void set_program_options(options_description& cli, options_description& cfg) override {}
   void plugin_initialize(const variables_map& vm) {}
   void plugin_startup();
   void plugin_shutdown() {}

   void dump(string dir);

private:
};

}
