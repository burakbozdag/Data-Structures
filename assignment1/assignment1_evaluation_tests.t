- init:
    run: rm -f assignment1
    blocker: true

- build:
    run: g++ -Wall -Werror assignment1.cpp -o assignment1  # timeout: 3
    blocker: true

- case1_grid_no_error:
    run: ./assignment1 grid_no_error.txt inst_no_error.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 7 7[ \r\n]*"                                     # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator - with size 1 is placed on [(]7,6[)].[ \r\n]*"    # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]3,5[)].[ \r\n]*"  # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]2,4[)].[ \r\n]*"    # timeout: 3
        - expect: "[ \r\n]*SUCCESS: - moved from [(]7,6[)] to [(]6,6[)].[ \r\n]*"              # timeout: 3
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,5[)] to [(]3,6[)].[ \r\n]*"            # timeout: 3
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]6,3[)].[ \r\n]*"              # timeout: 3
        - expect: "[ \r\n]*SUCCESS: / moved from [(]2,4[)] to [(]2,3[)].[ \r\n]*"              # timeout: 3
        - expect: _EOF_                                                                        # timeout: 3
    return: 0

- case2_grid_no_error_jump:
    run: ./assignment1 grid_no_error_jump.txt inst_no_error_jump.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 7 7[ \r\n]*"                                     # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 1 is placed on [(]2,2[)].[ \r\n]*"  # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator x with size 2 is placed on [(]5,3[)].[ \r\n]*"    # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator / with size 2 is placed on [(]4,3[)].[ \r\n]*"    # timeout: 3
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,3[)] to [(]5,5[)].[ \r\n]*"              # timeout: 3
        - expect: "[ \r\n]*SUCCESS: x moved from [(]5,5[)] to [(]3,5[)].[ \r\n]*"              # timeout: 3
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]2,2[)] to [(]3,2[)].[ \r\n]*"            # timeout: 3
        - expect: _EOF_                                                                        # timeout: 3
    return: 0

- case3_grid_border_error:
    run: ./assignment1 grid_border_error.txt inst_border_error.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 6 7[ \r\n]*"
        - expect: "[ \r\n]*SUCCESS: Operator [+] with size 2 is placed on [(]3,3[)].[ \r\n]*"             # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator - with size 2 is placed on [(]6,3[)].[ \r\n]*"               # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator / with size 1 is placed on [(]3,6[)].[ \r\n]*"               # timeout: 3
        - expect: "[ \r\n]*BORDER ERROR: Operator x with size 1 can not be placed on [(]6,6[)].[ \r\n]*"  # timeout: 3
        - expect: "[ \r\n]*SUCCESS: / moved from [(]3,6[)] to [(]4,6[)].[ \r\n]*"                         # timeout: 3
        - expect: "[ \r\n]*SUCCESS: [+] moved from [(]3,3[)] to [(]3,4[)].[ \r\n]*"                       # timeout: 3
        - expect: "[ \r\n]*BORDER ERROR: - can not be moved from [(]6,3[)] to [(]6,2[)].[ \r\n]*"         # timeout: 3
        - expect: _EOF_                                                                                   # timeout: 3
    return: 0

- case4_grid_conflict_error:
    run: ./assignment1 grid_conflict_error.txt inst_conflict_error.txt
    points: 10
    script:
        - expect: "[ \r\n]*A grid is created: 3 5[ \r\n]*"                                                  # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,2[)].[ \r\n]*"                 # timeout: 3
        - expect: "[ \r\n]*SUCCESS: Operator x with size 1 is placed on [(]2,3[)].[ \r\n]*"                 # timeout: 3
        - expect: "[ \r\n]*CONFLICT ERROR: Operator x with size 1 can not be placed on [(]2,4[)].[ \r\n]*"  # timeout: 3
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,2[)] to [(]2,4[)].[ \r\n]*"                           # timeout: 3
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,4[)].[ \r\n]*"         # timeout: 3
        - expect: "[ \r\n]*CONFLICT ERROR: x can not be moved from [(]2,3[)] to [(]2,2[)].[ \r\n]*"         # timeout: 3
        - expect: "[ \r\n]*SUCCESS: x moved from [(]2,4[)] to [(]2,2[)].[ \r\n]*"                           # timeout: 3
        - expect: _EOF_                                                                                     # timeout: 3
    return: 0
