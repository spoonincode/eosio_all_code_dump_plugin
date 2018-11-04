#include <fc/variant.hpp>
#include <fc/io/json.hpp>
#include <boost/filesystem/fstream.hpp>
#include <all_code_dump_plugin.hpp>

namespace eosio {

static appbase::abstract_plugin& _all_code_dump_plugin = app().register_plugin<all_code_dump_plugin>();

using namespace eosio;

struct code_dump_empty_thing{};

#define CALL(api_name, api_handle, call_name, INVOKE, http_response_code) \
{std::string("/v1/" #api_name "/" #call_name), \
   [api_handle](string, string body, url_response_callback cb) mutable { \
          try { \
             if (body.empty()) body = "{}"; \
             INVOKE \
             cb(http_response_code, fc::json::to_string(result)); \
          } catch (...) { \
             http_plugin::handle_exception(#api_name, #call_name, body, cb); \
          } \
       }}

#define INVOKE_V_R(api_handle, call_name, in_param) \
     api_handle->call_name(fc::json::from_string(body).as<in_param>()); \
     code_dump_empty_thing result;


void all_code_dump_plugin::plugin_startup() {
   app().get_plugin<http_plugin>().add_api({
       CALL(all_code_dump, this, dump,
            INVOKE_V_R(this, dump, string), 200),
   });
}

void all_code_dump_plugin::dump(string dir) {
   boost::filesystem::path dump_dir = app().data_dir() / dir;
   boost::filesystem::create_directory(dump_dir);

   auto acct_midx = app().get_plugin<chain_plugin>().chain().db().get_index<chain::account_index>().indices();
   for(const auto& a : acct_midx) {
      if(!a.code.size())
         continue;
      boost::filesystem::ofstream ofs(dump_dir / (a.name.to_string()+".wasm"), std::ofstream::binary);
      if(ofs)
         ofs.write(a.code.data(), a.code.size());
   }
}

}

FC_REFLECT(eosio::code_dump_empty_thing, );

