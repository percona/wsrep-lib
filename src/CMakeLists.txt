#
# Copyright (C) 2018 Codership Oy <info@codership.com>
#

set(WSREP_LIB_SOURCE_FILES
  allowlist_service_v1.cpp
  client_state.cpp
  config_service_v1.cpp
  connection_monitor_service_v1.cpp
  event_service_v1.cpp
  exception.cpp
  gtid.cpp
  id.cpp
  key.cpp
  logger.cpp
  provider.cpp
  provider_options.cpp
  reporter.cpp
  seqno.cpp
  server_state.cpp
  sr_key_set.cpp
  streaming_context.cpp
  thread.cpp
  thread_service_v1.cpp
  tls_service_v1.cpp
  transaction.cpp
  uuid.cpp
  view.cpp
  wsrep_provider_v26.cpp
  xid.cpp
  )

add_library(wsrep-lib
  ${WSREP_LIB_SOURCE_FILES}
  )

target_link_libraries(wsrep-lib wsrep_api_v26 pthread ${WSREP_LIB_LIBDL})

if (WSREP_LIB_WITH_UNIT_TESTS OR WSREP_LIB_WITH_UNIT_TESTS_EXTRA)
  add_library(wsrep-lib-unittest
    ${WSREP_LIB_SOURCE_FILES}
    )
  target_compile_definitions(
    wsrep-lib-unittest
    PRIVATE
    -DWSREP_LIB_WITH_UNIT_TESTS
    )

   target_link_libraries(wsrep-lib-unittest wsrep_api_v26 pthread ${WSREP_LIB_LIBDL})
endif()
