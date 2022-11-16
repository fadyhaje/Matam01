#ifndef ASCIIARTTOOL_H
#define ASCIIARTTOOL_H

#include "RLEList.h"
#include <stdio.h>


/**
 * The following functions are available:
 * asciiArtRead       - Given an art returns a compressed RLE list
 * asciiArtPrint      - Given an RLE list prints the art
 * asciiPrintEncoded  - Given an RLE list returns the compressed version of the art
 *
 */

/**
 * asciiArtRead: compresses the art from a file to an RLE
 *
 * @param in_stream - Reading from this file
 * @return  RLEList - Returns the a compressed list fits with the text in in_stream file
 */
RLEList asciiArtRead(FILE* in_stream);
/**
 * asciiArtPrint: Prints the image from a compressed RLE
 *
 * @param list             - Reading from this file
 * @param out_stream       - Writing to this file
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
 *     RLE_LIST_SUCCESS if the function printed the list successfully.
 */
RLEListResult asciiArtPrint(RLEList list, FILE* out_stream);
/**
 * asciiArtPrintEncoded: Given RLE list types the compressed RLE to the file @param out_stream
 *
 * @param list             - Rading this RLElist
 * @param out_stream       - Writing to this file
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
 *     RLE_LIST_SUCCESS if the encoding is done successfully.
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE* out_stream);

#endif
