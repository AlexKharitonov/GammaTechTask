set(API_FILE_NAME api)
set(API_SCHEMA_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${API_FILE_NAME}.fbs)
set(API_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/FiguresClient)
set(API_GENERATED_FILE ${API_OUTPUT_DIR}/${API_FILE_NAME}_generated.h)

add_custom_command(
    OUTPUT ${API_GENERATED_FILE}
    COMMAND ${FLATC} --cpp -o ${API_OUTPUT_DIR} ${API_SCHEMA_FILE}
    DEPENDS ${API_SCHEMA_FILE}
    COMMENT "Generating C++ headers from ${API_SCHEMA_FILE}"
)

add_custom_target(GenerateFlatBuffers DEPENDS ${API_GENERATED_FILE})
add_dependencies(GenerateFlatBuffers flatc)