add_executable(main acionamentos.c game_features.c musicas.c main.c) 

# pull in common dependencies
target_link_libraries(main pico_stdlib)

# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(main)
