//////
//    _     _ _     _____ _____ 
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____  
//   \ \   / /  ___| __|  _ \ 
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/ 
//      \_/  |_|  |_|  |_|
//
u8 gxFontBase_8x16[] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 126, -127, -91, -127, -127, -91, -103, -127, -127, 126, 0, 0, 0, 0, 
    0, 0, 126, -1, -37, -1, -1, -37, -25, -1, -1, 126, 0, 0, 0, 0, 
    0, 0, 0, 0, 108, -2, -2, -2, -2, 124, 56, 16, 0, 0, 0, 0, 
    0, 0, 0, 0, 16, 56, 124, -2, 124, 56, 16, 0, 0, 0, 0, 0, 
    0, 0, 0, 24, 60, 60, -25, -25, -25, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, 0, 24, 60, 126, -1, -1, 126, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 60, 126, 126, 126, 126, 60, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1, -61, -127, -127, -127, -127, -61, -1, -1, -1, -1, -1, 
    0, 0, 0, 0, 0, 60, 102, 66, 66, 102, 60, 0, 0, 0, 0, 0, 
    -1, -1, -1, -1, -1, -61, -103, -67, -67, -103, -61, -1, -1, -1, -1, -1, 
    0, 0, 30, 6, 14, 26, 120, -52, -52, -52, -52, 120, 0, 0, 0, 0, 
    0, 0, 60, 102, 102, 102, 102, 60, 24, 126, 24, 24, 0, 0, 0, 0, 
    0, 0, 60, 102, 102, 102, 102, 60, 24, 126, 24, 24, 0, 0, 0, 0, 
    0, 0, 127, 99, 127, 99, 99, 99, 99, 103, -25, -26, -64, 0, 0, 0, 
    0, 0, 0, 24, 24, -37, 60, -25, 60, -37, 24, 24, 0, 0, 0, 0, 
    0, -128, -64, -32, -16, -8, -2, -8, -16, -32, -64, -128, 0, 0, 0, 0, 
    0, 2, 6, 14, 30, 62, -2, 62, 30, 14, 6, 2, 0, 0, 0, 0, 
    0, 0, 24, 60, 126, 24, 24, 24, 126, 60, 24, 0, 0, 0, 0, 0, 
    0, 0, 102, 102, 102, 102, 102, 102, 102, 0, 102, 102, 0, 0, 0, 0, 
    0, 0, 127, -37, -37, -37, 123, 27, 27, 27, 27, 27, 0, 0, 0, 0, 
    0, 124, -58, 96, 56, 108, -58, -58, 108, 56, 12, -58, 124, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, -2, -2, -2, -2, 0, 0, 0, 0, 
    0, 0, 24, 60, 126, 24, 24, 24, 126, 60, 24, 126, 0, 0, 0, 0, 
    0, 0, 24, 60, 126, 24, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0, 
    0, 0, 24, 24, 24, 24, 24, 24, 24, 126, 60, 24, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 24, 12, -2, 12, 24, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 48, 96, -2, 96, 48, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, -64, -64, -64, -2, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 40, 108, -2, 108, 40, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 16, 56, 56, 124, 124, -2, -2, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, -2, -2, 124, 124, 56, 56, 16, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 24, 60, 60, 60, 24, 24, 24, 0, 24, 24, 0, 0, 0, 0, 
    0, 102, 102, 102, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 108, 108, -2, 108, 108, 108, -2, 108, 108, 0, 0, 0, 0, 
    24, 24, 124, -58, -62, -64, 124, 6, 6, -122, -58, 124, 24, 24, 0, 0, 
    0, 0, 0, 0, -62, -58, 12, 24, 48, 96, -58, -122, 0, 0, 0, 0, 
    0, 0, 56, 108, 108, 56, 118, -36, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 48, 48, 48, 96, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 12, 24, 48, 48, 48, 48, 48, 48, 24, 12, 0, 0, 0, 0, 
    0, 0, 48, 24, 12, 12, 12, 12, 12, 12, 24, 48, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 102, 60, -1, 60, 102, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 24, 24, 126, 24, 24, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 24, 48, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 
    0, 0, 0, 0, 2, 6, 12, 24, 48, 96, -64, -128, 0, 0, 0, 0, 
    0, 0, 56, 108, -58, -58, -42, -42, -58, -58, 108, 56, 0, 0, 0, 0, 
    0, 0, 24, 56, 120, 24, 24, 24, 24, 24, 24, 126, 0, 0, 0, 0, 
    0, 0, 124, -58, 6, 12, 24, 48, 96, -64, -58, -2, 0, 0, 0, 0, 
    0, 0, 124, -58, 6, 6, 60, 6, 6, 6, -58, 124, 0, 0, 0, 0, 
    0, 0, 12, 28, 60, 108, -52, -2, 12, 12, 12, 30, 0, 0, 0, 0, 
    0, 0, -2, -64, -64, -64, -4, 6, 6, 6, -58, 124, 0, 0, 0, 0, 
    0, 0, 56, 96, -64, -64, -4, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, -2, -58, 6, 6, 12, 24, 48, 48, 48, 48, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, -58, 124, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, -58, 126, 6, 6, 6, 12, 120, 0, 0, 0, 0, 
    0, 0, 0, 0, 24, 24, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 24, 24, 0, 0, 0, 24, 24, 48, 0, 0, 0, 0, 
    0, 0, 0, 6, 12, 24, 48, 96, 48, 24, 12, 6, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 126, 0, 0, 126, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 96, 48, 24, 12, 6, 12, 24, 48, 96, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, 12, 24, 24, 24, 0, 24, 24, 0, 0, 0, 0, 
    0, 0, 0, 124, -58, -58, -34, -34, -34, -36, -64, 124, 0, 0, 0, 0, 
    0, 0, 16, 56, 108, -58, -58, -2, -58, -58, -58, -58, 0, 0, 0, 0, 
    0, 0, -4, 102, 102, 102, 124, 102, 102, 102, 102, -4, 0, 0, 0, 0, 
    0, 0, 60, 102, -62, -64, -64, -64, -64, -62, 102, 60, 0, 0, 0, 0, 
    0, 0, -8, 108, 102, 102, 102, 102, 102, 102, 108, -8, 0, 0, 0, 0, 
    0, 0, -2, 102, 98, 104, 120, 104, 96, 98, 102, -2, 0, 0, 0, 0, 
    0, 0, -2, 102, 98, 104, 120, 104, 96, 96, 96, -16, 0, 0, 0, 0, 
    0, 0, 60, 102, -62, -64, -64, -34, -58, -58, 102, 58, 0, 0, 0, 0, 
    0, 0, -58, -58, -58, -58, -2, -58, -58, -58, -58, -58, 0, 0, 0, 0, 
    0, 0, 60, 24, 24, 24, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, 30, 12, 12, 12, 12, 12, -52, -52, -52, 120, 0, 0, 0, 0, 
    0, 0, -26, 102, 102, 108, 120, 120, 108, 102, 102, -26, 0, 0, 0, 0, 
    0, 0, -16, 96, 96, 96, 96, 96, 96, 98, 102, -2, 0, 0, 0, 0, 
    0, 0, -58, -18, -2, -2, -42, -58, -58, -58, -58, -58, 0, 0, 0, 0, 
    0, 0, -58, -26, -10, -2, -34, -50, -58, -58, -58, -58, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, -58, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, -4, 102, 102, 102, 124, 96, 96, 96, 96, -16, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, -58, -58, -58, -58, -42, -34, 124, 12, 14, 0, 0, 
    0, 0, -4, 102, 102, 102, 124, 108, 102, 102, 102, -26, 0, 0, 0, 0, 
    0, 0, 124, -58, -58, 96, 56, 12, 6, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, 126, 126, 90, 24, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, -58, -58, -58, -58, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, -58, -58, -58, -58, -58, -58, -58, 108, 56, 16, 0, 0, 0, 0, 
    0, 0, -58, -58, -58, -58, -42, -42, -42, -2, -18, 108, 0, 0, 0, 0, 
    0, 0, -58, -58, 108, 124, 56, 56, 124, 108, -58, -58, 0, 0, 0, 0, 
    0, 0, 102, 102, 102, 102, 60, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, -2, -58, -122, 12, 24, 48, 96, -62, -58, -2, 0, 0, 0, 0, 
    0, 0, 60, 48, 48, 48, 48, 48, 48, 48, 48, 60, 0, 0, 0, 0, 
    0, 0, 0, -128, -64, -32, 112, 56, 28, 14, 6, 2, 0, 0, 0, 0, 
    0, 0, 60, 12, 12, 12, 12, 12, 12, 12, 12, 60, 0, 0, 0, 0, 
    16, 56, 108, -58, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 
    48, 48, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 120, 12, 124, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 0, -32, 96, 96, 120, 108, 102, 102, 102, 102, 124, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 124, -58, -64, -64, -64, -58, 124, 0, 0, 0, 0, 
    0, 0, 28, 12, 12, 60, 108, -52, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 124, -58, -2, -64, -64, -58, 124, 0, 0, 0, 0, 
    0, 0, 56, 108, 100, 96, -16, 96, 96, 96, 96, -16, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 118, -52, -52, -52, -52, -52, 124, 12, -52, 120, 0, 
    0, 0, -32, 96, 96, 108, 118, 102, 102, 102, 102, -26, 0, 0, 0, 0, 
    0, 0, 24, 24, 0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, 6, 6, 0, 14, 6, 6, 6, 6, 6, 6, 102, 102, 60, 0, 
    0, 0, -32, 96, 96, 102, 108, 120, 120, 108, 102, -26, 0, 0, 0, 0, 
    0, 0, 56, 24, 24, 24, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -20, -2, -42, -42, -42, -42, -58, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -36, 102, 102, 102, 102, 102, 102, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 124, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -36, 102, 102, 102, 102, 102, 124, 96, 96, -16, 0, 
    0, 0, 0, 0, 0, 118, -52, -52, -52, -52, -52, 124, 12, 12, 30, 0, 
    0, 0, 0, 0, 0, -36, 118, 102, 96, 96, 96, -16, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 124, -58, 96, 56, 12, -58, 124, 0, 0, 0, 0, 
    0, 0, 16, 48, 48, -4, 48, 48, 48, 48, 54, 28, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -52, -52, -52, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 102, 102, 102, 102, 102, 60, 24, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -58, -58, -42, -42, -42, -2, 108, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -58, 108, 56, 56, 56, 108, -58, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -58, -58, -58, -58, -58, -58, 126, 6, 12, -8, 0, 
    0, 0, 0, 0, 0, -2, -52, 24, 48, 96, -58, -2, 0, 0, 0, 0, 
    0, 0, 14, 24, 24, 24, 112, 24, 24, 24, 24, 14, 0, 0, 0, 0, 
    0, 0, 24, 24, 24, 24, 0, 24, 24, 24, 24, 24, 0, 0, 0, 0, 
    0, 0, 112, 24, 24, 24, 14, 24, 24, 24, 24, 112, 0, 0, 0, 0, 
    0, 0, 118, -36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 16, 56, 108, -58, -58, -58, -2, 0, 0, 0, 0, 0, 
    14, 62, 126, 126, -2, -2, -2, -2, -2, -2, -2, -2, 126, 126, 62, 14, 
    14, 62, 66, 66, -62, -62, -62, -2, -2, -2, -2, -2, 126, 126, 62, 14, 
    14, 62, 126, 126, -2, -2, -2, -2, -2, -62, -62, -62, 66, 66, 62, 14, 
    14, 62, 66, 66, -62, -62, -62, -62, -62, -62, -62, -62, 66, 66, 62, 14, 
    -16, -8, -4, -2, -2, -2, -1, -1, -1, -1, -2, -2, -2, -4, -8, -16, 
    -16, -8, -60, -58, -58, -58, -57, -1, -1, -1, -2, -2, -2, -4, -8, -16, 
    -16, -8, -4, -2, -2, -2, -1, -1, -1, -57, -58, -58, -58, -60, -8, -16, 
    -16, -8, -60, -58, -58, -58, -57, -57, -57, -57, -58, -58, -58, -60, -8, -16, 
    126, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 126, 
    126, -2, -58, -58, -58, -58, -58, -2, -2, -2, -2, -2, -2, -2, -2, 126, 
    126, -2, -2, -2, -2, -2, -2, -2, -2, -58, -58, -58, -58, -58, -2, 126, 
    126, -2, -58, -58, -58, -58, -58, -58, -58, -58, -58, -58, -58, -58, -2, 126, 
    -4, -2, -2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -2, -2, -4, 
    -4, -2, -62, -61, -61, -61, -61, -1, -1, -1, -1, -1, -1, -2, -2, -4, 
    -4, -2, -2, -1, -1, -1, -1, -1, -1, -61, -61, -61, -61, -62, -2, -4, 
    -4, -2, -62, -61, -61, -61, -61, -61, -61, -61, -61, -61, -61, -62, -2, -4, 
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, -2, 
    -2, -2, -114, -114, -114, -114, -114, -2, -2, -2, -2, -2, -2, -2, -2, -2, 
    -2, -2, -2, -2, -2, -2, -2, -2, -2, -114, -114, -114, -114, -114, -2, -2, 
    -2, -2, -114, -114, -114, -114, -114, -114, -114, -114, -114, -114, -114, -114, -2, -2, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -31, -31, -31, -31, -31, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -31, -31, -31, -31, -31, -1, -1, 
    -1, -1, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -1, -1, 
    0, 0, -58, 0, 0, -58, -58, -58, -58, -58, -58, 126, 6, 12, 120, 0, 
    0, -58, 0, 124, -58, -58, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, -58, 0, -58, -58, -58, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 24, 24, 60, 102, 96, 96, 96, 102, 60, 24, 24, 0, 0, 0, 0, 
    0, 56, 108, 100, 96, -16, 96, 96, 96, 96, -26, -4, 0, 0, 0, 0, 
    0, 0, 102, 102, 60, 24, 126, 24, 126, 24, 24, 24, 0, 0, 0, 0, 
    0, -8, -52, -52, -8, -60, -52, -34, -52, -52, -52, -58, 0, 0, 0, 0, 
    0, 14, 27, 24, 24, 24, 126, 24, 24, 24, 24, 24, -40, 112, 0, 0, 
    0, 24, 48, 96, 0, 120, 12, 124, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 12, 24, 48, 0, 56, 24, 24, 24, 24, 24, 60, 0, 0, 0, 0, 
    0, 24, 48, 96, 0, 124, -58, -58, -58, -58, -58, 124, 0, 0, 0, 0, 
    0, 24, 48, 96, 0, -52, -52, -52, -52, -52, -52, 118, 0, 0, 0, 0, 
    0, 0, 118, -36, 0, -36, 102, 102, 102, 102, 102, 102, 0, 0, 0, 0, 
    118, -36, 0, -58, -26, -10, -2, -34, -50, -58, -58, -58, 0, 0, 0, 0, 
    0, 60, 108, 108, 62, 0, 126, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 56, 108, 108, 56, 0, 124, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 48, 48, 0, 48, 48, 96, -64, -58, -58, 124, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, -2, -64, -64, -64, -64, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, -2, 6, 6, 6, 6, 0, 0, 0, 0, 0, 
    0, -64, -64, -62, -58, -52, 24, 48, 96, -36, -122, 12, 24, 62, 0, 0, 
    0, -64, -64, -62, -58, -52, 24, 48, 102, -50, -98, 62, 6, 6, 0, 0, 
    0, 0, 24, 24, 0, 24, 24, 24, 60, 60, 60, 24, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 54, 108, -40, 108, 54, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -40, 108, 54, 108, -40, 0, 0, 0, 0, 0, 0, 
    17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 17, 68, 
    85, -86, 85, -86, 85, -86, 85, -86, 85, -86, 85, -86, 85, -86, 85, -86, 
    -35, 119, -35, 119, -35, 119, -35, 119, -35, 119, -35, 119, -35, 119, -35, 119, 
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 
    96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 
    24, 24, 24, 24, 24, -8, 24, -8, 24, 24, 24, 24, 24, 24, 24, 24, 
    54, 54, 54, 54, 54, 54, 54, -10, 54, 54, 54, 54, 54, 54, 54, 54, 
    0, 0, 0, 0, 0, 0, 0, -2, 54, 54, 54, 54, 54, 54, 54, 54, 
    0, 0, 0, 0, 0, -8, 24, -8, 24, 24, 24, 24, 24, 24, 24, 24, 
    54, 54, 54, 54, 54, -10, 6, -10, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 
    0, 0, 0, 0, 0, -2, 6, -10, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, -10, 6, -2, 0, 0, 0, 0, 0, 0, 0, 0, 
    54, 54, 54, 54, 54, 54, 54, -2, 0, 0, 0, 0, 0, 0, 0, 0, 
    24, 24, 24, 24, 24, -8, 24, -8, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, -8, 24, 24, 24, 24, 24, 24, 24, 24, 
    96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 127, 127, 0, 
    24, 24, 24, 24, 24, 24, 24, -1, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, -1, 24, 24, 24, 24, 24, 24, 24, 24, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 
    0, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    24, 24, 24, 24, 24, 24, 24, -1, 24, 24, 24, 24, 24, 24, 24, 24, 
    24, 24, 24, 24, 24, 31, 24, 31, 24, 24, 24, 24, 24, 24, 24, 24, 
    54, 54, 54, 54, 54, 54, 54, 55, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, 55, 48, 63, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 63, 48, 55, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, -9, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -1, 0, -9, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, 55, 48, 55, 54, 54, 54, 54, 54, 54, 54, 54, 
    0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 
    54, 54, 54, 54, 54, -9, 0, -9, 54, 54, 54, 54, 54, 54, 54, 54, 
    24, 24, 24, 24, 24, -1, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 
    54, 54, 54, 54, 54, 54, 54, -1, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, -1, 0, -1, 24, 24, 24, 24, 24, 24, 24, 24, 
    0, 0, 0, 0, 0, 0, 0, -1, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, 54, 54, 63, 0, 0, 0, 0, 0, 0, 0, 0, 
    24, 24, 24, 24, 24, 31, 24, 31, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 31, 24, 31, 24, 24, 24, 24, 24, 24, 24, 24, 
    0, 0, 0, 0, 0, 0, 0, 63, 54, 54, 54, 54, 54, 54, 54, 54, 
    54, 54, 54, 54, 54, 54, 54, -1, 54, 54, 54, 54, 54, 54, 54, 54, 
    24, 24, 24, 24, 24, -1, 24, -1, 24, 24, 24, 24, 24, 24, 24, 24, 
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, -2, -2, 0, 
    0, 127, 127, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, 
    -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, 
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 
    -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 118, -36, -40, -40, -40, -36, 118, 0, 0, 0, 0, 
    0, 0, 120, -52, -52, -52, -40, -52, -58, -58, -58, -52, 0, 0, 0, 0, 
    0, 0, -2, -58, -58, -64, -64, -64, -64, -64, -64, -64, 0, 0, 0, 0, 
    0, 0, 0, 0, -2, 108, 108, 108, 108, 108, 108, 108, 0, 0, 0, 0, 
    0, 0, 0, -2, -58, 96, 48, 24, 48, 96, -58, -2, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 126, -40, -40, -40, -40, -40, 112, 0, 0, 0, 0, 
    0, 0, 0, 0, 102, 102, 102, 102, 102, 124, 96, 96, -64, 0, 0, 0, 
    0, 0, 0, 0, 118, -36, 24, 24, 24, 24, 24, 24, 0, 0, 0, 0, 
    0, 0, 0, 126, 24, 60, 102, 102, 102, 60, 24, 126, 0, 0, 0, 0, 
    0, 0, 0, 56, 108, -58, -58, -2, -58, -58, 108, 56, 0, 0, 0, 0, 
    0, 0, 56, 108, -58, -58, -58, 108, 108, 108, 108, -18, 0, 0, 0, 0, 
    0, 0, 30, 48, 24, 12, 62, 102, 102, 102, 102, 60, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 126, -37, -37, -37, 126, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 3, 6, 126, -37, -37, -13, 126, 96, -64, 0, 0, 0, 0, 
    0, 0, 28, 48, 96, 96, 124, 96, 96, 96, 48, 28, 0, 0, 0, 0, 
    0, 0, 0, 124, -58, -58, -58, -58, -58, -58, -58, -58, 0, 0, 0, 0, 
    0, 0, 0, 0, -2, 0, 0, -2, 0, 0, -2, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 24, 24, 126, 24, 24, 0, 0, -1, 0, 0, 0, 0, 
    0, 0, 0, 48, 24, 12, 6, 12, 24, 48, 0, 126, 0, 0, 0, 0, 
    0, 0, 0, 12, 24, 48, 96, 48, 24, 12, 0, 126, 0, 0, 0, 0, 
    0, 0, 14, 27, 27, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 
    24, 24, 24, 24, 24, 24, 24, 24, -40, -40, -40, 112, 0, 0, 0, 0, 
    0, 0, 0, 0, 24, 24, 0, 126, 0, 24, 24, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 118, -36, 0, 118, -36, 0, 0, 0, 0, 0, 0, 
    0, 56, 108, 108, 56, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 24, 24, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 
    0, 15, 12, 12, 12, 12, 12, -20, 108, 108, 60, 28, 0, 0, 0, 0, 
    0, -40, 108, 108, 108, 108, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 112, -40, 48, 96, -56, -8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 124, 124, 124, 124, 124, 124, 124, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
};