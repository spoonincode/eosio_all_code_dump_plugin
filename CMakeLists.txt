add_library( all_code_dump_plugin
             all_code_dump_plugin.cpp
             all_code_dump_plugin.hpp )

target_link_libraries( all_code_dump_plugin http_plugin chain_plugin )
target_include_directories( all_code_dump_plugin PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}" )

eosio_additional_plugin(all_code_dump_plugin)
