                  // See if we're passed the first bit of data on the line (cursor is something like: "  _This is a test")
                  check_bol:
                    i = 0;
                    while (i < _offset) {
                        c1 = *(input[current_input].ptr + i);
                        if (c1 == 32 || c1 == '_') {
                            goto try_again;
                        }
                        ++i;
                    }
                  // If we make it here, there is nothing between the start of the line and the cursor's current location
                    _offset = 0;