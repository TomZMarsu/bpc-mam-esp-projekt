idf_component_register(SRCS "blink_example_main.c" 
                            "1_blink/1_blink.c"
                            "2_wifi/2_wifi.c"
                            "3_ntp/3_ntp.c"
                       INCLUDE_DIRS "." "1_blink" "2_wifi" "3_ntp")
