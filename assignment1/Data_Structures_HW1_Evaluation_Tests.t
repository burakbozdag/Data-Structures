- init:
    run: rm -f assignment1
    blocker: true

- build:
    run: g++ -Wall -Werror assignment1.cpp -o assignment1  # timeout: 8
    blocker: true

- case1_grid_no_error_jump:
    run: ./assignment1 no_error_jump_grid.txt no_error_jump_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 7 7[ \r\n]*"                                     # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,2[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 2 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 2 is placed on [(]4,3[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]5,5[)].[ \r\n]*"              # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,5[)] to [(]3,5[)].[ \r\n]*"              # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,2[)] to [(]3,2[)].[ \r\n]*"            # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0


- case2_grid_no_error:
    run: ./assignment1 no_error_grid.txt no_error_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 7 7[ \r\n]*"                                     # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]7,6[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]3,5[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]2,4[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]7,6[)] to [(]6,6[)].[ \r\n]*"              # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,5[)] to [(]3,6[)].[ \r\n]*"            # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]6,3[)].[ \r\n]*"              # timeout: 8
        - expect: "[ \r\n]*SUCCESS: / moved from [(]2,4[)] to [(]2,3[)].[ \r\n]*"              # timeout: 8
        - expect: _EOF_                                                                        # timeout: 8
    return: 0


- case3_grid_conflict_error:
    run: ./assignment1 conflict_error_grid.txt conflict_error_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 3 5[ \r\n]*"                                                  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,2[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,3[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: Operator x with size 1 can not be placed on [(]2,4[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,2[)] to [(]2,4[)].[ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,4[)].[ \r\n]*"         # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,2[)].[ \r\n]*"         # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,4[)] to [(]2,2[)].[ \r\n]*"                           # timeout: 8
        - expect: _EOF_                                                                                     # timeout: 8
    return: 0


- case4_grid_border_error:
    run: ./assignment1 border_error_grid.txt border_error_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 6 7[ \r\n]*"                                                # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 2 is placed on [(]3,3[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]6,3[)].[ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]3,6[)].[ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: Operator x with size 1 can not be placed on [(]6,6[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: / moved from [(]3,6[)] to [(]4,6[)].[ \r\n]*"                         # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"                       # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: - can not be moved from [(]6,3[)] to [(]6,2[)].[ \r\n]*"         # timeout: 8
        - expect: _EOF_                                                                                   # timeout: 8
    return: 0


- case5_plus_rotate:
    run: ./assignment1 plus_rotate_grid.txt plus_rotate_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 6 7[ \r\n]*"                                      # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,2[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,3[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,6[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,6[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,2[)] to [(]3,2[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,6[)] to [(]2,5[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]5,6[)] to [(]4,6[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]5,3[)] to [(]5,4[)].[ \r\n]*"             # timeout: 8
        - expect: _EOF_                                                                         # timeout: 8
    return: 0


- case6_minus_adjacent:
    run: ./assignment1 minus_adjacent_grid.txt minus_adjacent_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 5 8[ \r\n]*"                                    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]1,3[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]1,7[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]2,7[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]3,3[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 3 is placed on [(]4,4[)].[ \r\n]*"   # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]1,3[)] to [(]2,3[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]2,7[)] to [(]3,7[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]1,7[)] to [(]2,7[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]4,4[)] to [(]5,4[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]3,7[)] to [(]4,7[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]4,7[)] to [(]4,6[)].[ \r\n]*"             # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]5,4[)] to [(]5,5[)].[ \r\n]*"             # timeout: 8
        - expect: _EOF_                                                                       # timeout: 8
    return: 0


- case8_div_border_conflict:
    run: ./assignment1 div_border_conflict_grid.txt div_border_conflict_inst.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 5 5[ \r\n]*"                                           # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]3,2[)].[ \r\n]*"          # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 2 is placed on [(]3,3[)].[ \r\n]*"          # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]4,3[)].[ \r\n]*"          # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]3,2[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]3,2[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]2,3[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]2,3[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]3,3[)] to [(]4,3[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]3,3[)] to [(]4,3[)].[ \r\n]*"  # timeout: 8
        - expect: _EOF_                                                                              # timeout: 8
    return: 0


- case9_crowded:
    run: ./assignment1 crowded_grid.txt crowded_inst.txt
    points: 15
    script:
        - expect: "[ \r\n]*A grid is created: 10 7[ \r\n]*"                                                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,2[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,4[)].[ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,6[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: Operator / with size 9 can not be placed on [(]2,1[)].[ \r\n]*"    # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 3 is placed on [(]9,4[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 3 is placed on [(]5,4[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: Operator - with size 3 can not be placed on [(]5,4[)].[ \r\n]*"  # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]5,2[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]7,6[)].[ \r\n]*"                 # timeout: 8
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]5,6[)].[ \r\n]*"               # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,2[)] to [(]4,2[)].[ \r\n]*"         # timeout: 8
        - expect: "[ \r\n]*SUCCESS: - moved from [(]5,2[)] to [(]10,2[)].[ \r\n]*"                          # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,2[)] to [(]4,2[)].[ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: [+] can not be moved from [(]2,4[)] to [(]2,3[)].[ \r\n]*"       # timeout: 8
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,4[)] to [(]2,2[)].[ \r\n]*"                         # timeout: 8
        - expect: "[ \r\n]*SUCCESS: / moved from [(]7,6[)] to [(]7,3[)].[ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,6[)] to [(]7,6[)].[ \r\n]*"                           # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: - can not be moved from [(]10,2[)] to [(]10,9[)].[ \r\n]*"         # timeout: 8
        - expect: "[ \r\n]*BORDER ERROR: / can not be moved from [(]5,4[)] to [(]2,4[)].[ \r\n]*"           # timeout: 8
        - expect: "[ \r\n]*CONFLICT ERROR: / can not be moved from [(]5,4[)] to [(]2,4[)].[ \r\n]*"         # timeout: 8
        - expect: _EOF_                                                                                     # timeout: 8
    return: 0


