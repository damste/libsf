//////////
//
// /libsf/utils/common/cpp/xml/xml.cpp
//
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
//////
// Version 0.10
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Aug.02.2014
//////
// Change log:
//     Aug.02.2014 - Initial creation
//////
//
// This document is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// The PBL is a public domain license with a caveat:  self accountability unto God.
// You are free to use, copy, modify and share this software for any purpose, however,
// it is the desire of those working on this project that the software remain open.
// It is our request that you maintain it that way.  This is not a legal request unto
// our court systems, but rather a personal matter between you and God.  Our talents
// were received from God, and given to you through this forum.  And it is our wish
// that those talents reach out to as many as possible in a form allowing them to wield
// this content for their own betterment, as you are now considering doing.  And whereas
// we could've forced the issue through something like a copyleft-protected release, the
// truth is we are all giving an account of our lives unto God continually by the daily
// choices we make.  And here again is another case where you get to demonstrate your
// character unto God, and unto your fellow man.
//
// Jesus came to this Earth to set the captives free, to save men's eternal souls from
// the punishment demanded by our sin.  Each one of us is given the opportunity to
// receive Him in this world and be saved.  Whether we choose to receive Him, and follow
// Him, and purpose our lives on the goals He has for each of us (all of which are
// beneficial for all involved), is one way we reveal our character continually.  God
// sees straight through to the heart, bypassing all of the words, all of the facades.
// He is our Creator, and He knows who we are truly.
//
// Jesus is called "Christ" because He saves men from the eternal flames of Hell, the
// just punishment of rebellion against God (rebellion against truth) by eternal beings,
// which each of us are.
//
// Do not let His free gift escape you because of some desire to shortcut what is right
// in your life. Instead, do what is right, and do it because He is who He is, and what
// He has done to save us from such a fate.  Demonstrate to Him, to me, and to all of
// mankind, and to all of the Heavenly hosts, exactly who you are on the inside.  Receive
// Jesus Christ into your heart, learn of Him, of how He came here to guide us into that
// which is of His Kingdom and will be forever hereafter we leave this world.  Do this,
// and live.
//
// Every project released by Liberty Software Foundation will include a copy of the
// pbl.txt document, which can be found at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//




//////////
//
// Load the file into a buffer, and then call the load algorithm to load it into an XML handle
//
//----------
// Error codes exist in range of -101 to -103 from this function, and -1 to -99 from the actual xml_load() function:
//
//		-101			- File could not be opened
//		-102			- Unable to allocate memory for load
//		-103			- Unable to read file into memory
//
/////
	uptr xml_load_file(cs8* filename)
	{
		return(xml_load_file((s8*)filename));
	}

	uptr xml_load_file(cu8* filename)
	{
		return(xml_load_file((s8*)filename));
	}

	uptr xml_load_file(u8* filename)
	{
		return(xml_load_file((s8*)filename));
	}

	uptr xml_load_file(s8* filename)
	{
		s32		lfh;
		s32		lnFileSize, lnNumread;
		uptr	lnReturnVal;
		s8*		tptr;


		// Open the file specified by the user
		lfh = _sopen(filename, _O_BINARY | _O_RDWR, _SH_DENYNO, _S_IREAD);
		if (!lfh)
			return(-101);		// No file could be opened


		// Find out how big it is
		lnFileSize = _lseek(lfh, 0, SEEK_END);
		_lseek(lfh, 0, SEEK_SET);


		// Allocate memory
		tptr = (s8*)malloc(lnFileSize);
		if (tptr == NULL)
			return(-102);		// Cannot allocate memory


		// Read into memory
		lnNumread = _read(lfh, tptr, lnFileSize);
		if (lnNumread != lnFileSize)
			return(-103);


		// Close the file
		_close(lfh);


		// Load it as XML
		lnReturnVal = xml_load(tptr, lnFileSize);


		// Note:  We cannot free the source buffer because the XML data points to the source, it does not copy it
		//free(tptr);


		// All done!
		return(lnReturnVal);
	}










//////////
//
// Physically parse the raw text of the input file.
//
// Note:  This process only accepts ASCII files.
//        It will not parse UNICODE or wide-character files.
//
//----------
// Error codes:
//		-1				- Syntax error
//		-2				- Syntax error
//
/////
	CXml* xml_loadAs_cxml(cs8* buffer, u32 tnLength)		{	return((CXml*)xml_load((s8*)buffer, tnLength));		}
	CXml* xml_loadAs_cxml(s8* buffer, u32 tnLength)			{	return((CXml*)xml_load(buffer, tnLength));			}
	CXml* xml_loadAs_cxml(cu8* buffer, u32 tnLength)		{	return((CXml*)xml_load((s8*)buffer, tnLength));		}
	CXml* xml_loadAs_cxml(u8* buffer, u32 tnLength)			{	return((CXml*)xml_load((s8*)buffer, tnLength));		}
	uptr xml_load(cs8* buffer, u32 tnLength)				{	return(xml_load((s8*)buffer, tnLength));			}
	uptr xml_load(cu8* buffer, u32 tnLength)				{	return(xml_load((s8*)buffer, tnLength));			}
	uptr xml_load(u8* buffer, u32 tnLength)					{	return(xml_load((s8*)buffer, tnLength));			}

	uptr xml_load(s8* buffer, u32 tnLength)
	{
		u32 lnOffset, lnThis, lnLastSkip;
		bool lbStop;
		// Pointers used for holding the various items as we traverse the XML tree
		CXml*			loTag			= NULL;
		CXml*			loRoot			= NULL;
		CXml*			loNew			= NULL;
		XmlData*		loCData			= NULL;
		XmlData*		loData			= NULL;
		XmlData*		loTagNameData	= NULL;


		// We must now be at the root node
		lnOffset = 0;
		if (tnLength <= 0)
			tnLength = (u32)strlen(buffer);

		// Beginning of a tag
		loTag   = new CXml();
		loRoot  = loTag;

		// Store a pointer to the full data set
		loData	= new XmlData();
		loData->set_data(buffer);
		loData->set_length(tnLength);
		loRoot->set_data(loData);

		// See what's there
		while (lnOffset < tnLength)
		{
			// Skip past initial white spaces
			lnThis = 0;
			iXml_load__skip_white_spaces(buffer, lnOffset, lnThis, tnLength);
			lnLastSkip = lnThis;
			lnOffset += lnThis;
			if (lnOffset >= tnLength)
			{
				// We've reached the end of the XML file
				break;
			}

			// Right now, we should be on the first non-whitespace character at (wherever we are in the file)
			lnThis = 0;
			if (buffer[lnOffset] == '<')
			{
				// See if it's a comment
				if (lnOffset + 1 < tnLength)
				{
					if (buffer[lnOffset + 1] == '!')
					{
// It is the start of some <! thing, could be <!--, <![CDATA[ or something else
						if (lnOffset + 3 < tnLength)
						{
							if (buffer[lnOffset + 2] == '-' && buffer[lnOffset + 3] == '-')
							{
		// Start of comment
								// Ignore to the end of the comment
								lnThis = 3;
								while (lnOffset + lnThis + 2 < tnLength)
								{
									if (buffer[lnOffset + lnThis + 0] == '-' && buffer[lnOffset + lnThis + 1] == '-' && buffer[lnOffset + lnThis + 2] == '>')
									{
										// It's the end of the comment
										lnThis += 3;
										break;
									}
									// Continue looking
									++lnThis;
								}

								// When we get here, we're at the end of the XML file, or we've found the end of the comment
								lnOffset += lnThis;
		// End of comment

							}
							else if (lnOffset + 9 < tnLength)
							{
								if (buffer[lnOffset + 1] == '!' &&
								    buffer[lnOffset + 2] == '[' &&
									buffer[lnOffset + 3] == 'C' &&
									buffer[lnOffset + 4] == 'D' &&
									buffer[lnOffset + 5] == 'A' &&
									buffer[lnOffset + 6] == 'T' &&
									buffer[lnOffset + 7] == 'A' &&
									buffer[lnOffset + 8] == '[')
								{
		// CDATA section
									// Copy until the closing ]]> string
									// Copy this literal section until we reach the end
									loCData = new XmlData();
									loCData->set_data(&buffer[lnOffset + 9]);
									lnOffset += 9;
									lnThis = 0;

									// Scan for the ending "]]>" characters
									while (lnOffset + lnThis + 3 < tnLength)
									{
										// See if we're at the end yet?
										if (buffer[lnOffset + lnThis + 0] == ']' && buffer[lnOffset + lnThis + 1] == ']' && buffer[lnOffset + lnThis + 2] == '>')
										{
											// We've reached the end
											break;
										}
										// Move to next position
										++lnThis;
									}
									if (lnOffset + lnThis + 3 >= tnLength)
									{
										// We've reached the end of the XML file
										// Syntax error
										return(-1);
									}
									// When we get here, regardless of whether or not we've reached the end of the CDATA section, we are finished (either end of CDATA or end of XML file)
									loCData->set_length(lnThis);
									lnOffset += lnThis + 3;
									lnThis = 0;
									// Right now, we're on the character immediate after whatever this thing we just found was
									if (!loTag->cdata())
									{
										// Store the CDATA section on this tag
										loTag->set_cdata(loCData);
									}
									else
									{
										// This is the nth CDATA section, which means we just ignore this duplicate
										delete loCData;
									}

								}
								else
								{
									// Don't know what it is.  Hmmm...
									// Ignore it to closing >
									while (lnOffset < tnLength && buffer[lnOffset] != '>')
									{
										++lnOffset;
									}
									// When we get here, we're past the closing >, so we should be able to continue on with a life full and rich, able to pursue our dreams without hindrance.

								}

							}
							else
							{
								// We don't know what it is.  Hmmm...
								// Ignore it to closing >
								while (lnOffset < tnLength && buffer[lnOffset] != '>')
								{
									++lnOffset;
								}
								// Ditto


							}

						}
						else
						{
							// End of XML file
							// All done processing
							break;
						}

					}
					else
					{
// New tag
						// This tag will include everything at this level and below, and which points then to the next item at the same level
						// Skip past the < character
						lnThis = 1;


						// See where we are
						if (buffer[lnOffset + lnThis] == '/')
						{
							// It's the closing of a tag
							// Find the name in the hierarchy to see where from it came
							if (lnOffset + lnThis + 1 >= tnLength)
							{
								// We've reached the end of the XML file
								break;
							}
							lnOffset += lnThis + 1;
							lnThis = 0;
							while (lnOffset + lnThis < tnLength)
							{
								if (buffer[lnOffset + lnThis] == '>' || buffer[lnOffset + lnThis] == ' ')
								{
									// We've found the end of the name
									break;
								}
								// Still going
								++lnThis;
							}
							if (lnOffset + lnThis >= tnLength)
							{
								// We've reached the end of the XML file, syntax error
								return(-1);
							}
							// The name we just found must match the immediate parent, or the item we're on
							while (loTag)
							{
								if (!loTag->is_closed())
								{
									// This tag is not closed yet
									// See if this is a match
									if (loTag->tag() && loTag->tag()->length() == lnThis)
									{
										// They're the same length
										// See if the data comparison is a match
										if (_memicmp(&buffer[lnOffset], loTag->tag()->as_s8p(), lnThis) == 0)
										{
											// This is a match
											loTag->set_closed();
											break;
										}
									}
								}
								// If it's not this item, it must be a parent item
								loTag = loTag->parent();
							}
							lnOffset += lnThis;
							lnThis = 0;

							// When we get here, we've either found the item or not
							if (!loTag || (loTag && !loTag->is_closed()))
							{
								// We did not find the match
								// Syntax error
								return(-1);

							}
							else
							{
								// Skip to closing > character
								iXml_load__skip_white_spaces(buffer, lnOffset, lnThis, tnLength);
								lnOffset += lnThis;
								if (buffer[lnOffset] != '>')
								{
									// Syntax error, needs to be the closing character
									return(-1);
								}
								if (lnOffset + 1 >= tnLength)
								{
									// We've reached the end of the XML file
									// If this was the last tag, that's okay, otherwise, not so much
									if (loTag->parent() != loRoot)
										return(-1);
									//else
									//We're good!
								}
								lnOffset += 1;
								// Right now, we're on the character immediately after the closing tag, ready for continued processing

							}

						}
						else
						{
							// It's the beginning of a tag
							// Create the new tag for this level
							loNew = new CXml();


							// Find out where this one gets added
							// Note:  loTag is the current tag we're sitting at/on.  This one will be added to it as either a child tag, or if there is already a child, then the next.
							// Note:  This logic is maintained through the processing path below.
							if (!loTag->is_closed())
							{
								if (loTag->child())
								{
									// The first child already exists, which means we've already traversed the children's branch.
									// Now, we are adding the next item
									loNew->set_parent(loTag->parent());
									loNew->set_prev(loTag);
									loTag->set_next(loNew);

								}
								else
								{
									// This is the first child
									loNew->set_parent(loTag);
									loTag->set_child(loNew);

								}

							}
							else
							{
								// The current level is closed
								// We add this one as a next
								loNew->set_parent(loTag->parent());
								loNew->set_prev(loTag);
								loTag->set_next(loNew);

							}
							// Update the current loTag to be the newly created loNew entry
							loTag = loNew;


							// Create the name portion of the new tag
							loTagNameData = new XmlData();
							loTagNameData->set_data(&buffer[lnOffset + lnThis]);
							loTag->set_tag(loTagNameData);


							// Iterate through everything to find out what we're doing
							lbStop				= false;
							while (!lbStop && lnOffset + lnThis < tnLength)
							{
								switch (buffer[lnOffset + lnThis])
								{
									case 32:
										// We've reached the space after the tag name
										loTagNameData->set_length(lnThis - 1);

										// Skip repeated spaces
										iXml_load__skip_white_spaces(buffer, lnOffset, lnThis, tnLength);

										// See what it is now
										switch (buffer[lnOffset + lnThis])
										{
											case '/':
												// It's the beginning of a closing tag, which means this was a single thing
												if (lnOffset + lnThis + 1 < tnLength)
												{
													// There is room for the trailing > after the /, indicating <tag />
													if (buffer[lnOffset + lnThis + 1] == '>')
													{
														// It's of proper format, we close this tag, and point back to the parent (if any)
														loTag->set_tag(loTagNameData);
														lnOffset += lnThis;
														// Right now, we have this tag closed by the trailing /> characters
														loTag->set_closed();
														// It can't have any other options because it closes
														// So we assume the next item will be a thing

													}
													else
													{
														// It's some kind of syntax error in the XML tag string, like <tag /blah
														// Ignore it, continue on until the closing >

													}

												}
												// Right now, we've either added the tag, or not, but regardless we continue
												break;

											case '>':
												// It's the end of a tag which has something after it
												break;

											default:
												// It's the beginning of an (a series of) attribute(s?)
												lnOffset	+= lnThis;
												lnThis		= 0;
												iXml_load__attributes(loTag, buffer, lnOffset, lnThis, tnLength);
												// After loading attributes, we are either sitting on / or > or are at end of the XML file due to an error
												// The ramifications of our position will be sorted out as processing continues
												break;
										}
										break;

									case '>':
										// We've reached the closing tag name
										if (loTagNameData->length() == 0)
											loTagNameData->set_length(lnThis - 1);		// We have not set the name length

										if (lnOffset + lnThis + 1 >= tnLength)
											break;		// End of XML file

										lnOffset += lnThis + 1;	 // +1 move past closing >
										// Indicate that we're done processing this tag (no attributes, on to whatever's next)
										lbStop = true;
										break;

									case '/':
										// We've reached the end of a single-item tag
										if (loTagNameData->length() == 0)
											loTagNameData->set_length(lnThis - 1);		// We have not set the name length


										if (lnOffset + lnThis + 1 >= tnLength)
											break;		// We've reached the end of the XML file

										// Move past the /
										lnOffset += lnThis + 1;
										if (buffer[lnOffset] != '>')
										{
											// Syntax error
											return(-1);
										}
										// Move past the >
										++lnOffset;

										// Close the current tag
										loTag->set_closed();
										// All done, we're ready for the next thing
										lbStop = true;
										break;

									default:
										++lnThis;
										break;
								}
							}
						}
						// When we get here, we've found the end of the tag, or reached the end of the XML file
						// In either case, we are ready to continue on to the next thing

					}

				}
				else
				{
					// We've reached the end
					++lnOffset;
					break;

				}

			}
			else
			{
				// This is data between tags, load it until we get to the next < character
				// It will end when we see a < character, or reach the end
				lnThis = 0;
				while (lnOffset + lnThis < tnLength)
				{
					if (buffer[lnOffset + lnThis] == '<')
					{
						// We've found the end of the thing
						break;
					}

					// Fixup any << or >> characters (ascii 171 and 187) that may have been encoded
					if (buffer[lnOffset + lnThis] == 0xab)
						buffer[lnOffset + lnThis] = '<';	// Convert to < character
					if (buffer[lnOffset + lnThis] == 0xbb)
						buffer[lnOffset + lnThis] = '>';	// Convert to >> character
					// Note: This fixup code relates to fixups made in xml.h's save__write_item() function

					// Move to the next position
					++lnThis;
				}

				// We've found the range of the thing
				loData = new XmlData();
				loData->set_data(&buffer[lnOffset - lnLastSkip]);		// The lnlastSkip is added because we don't skip past white spaces for data items
				loData->set_length(lnThis + lnLastSkip);

				// Move past this end thing
				lnOffset += lnThis;
				// Note:  If there are trailing spaces that are there as whitespaces, they ARE included in this text portion

				// Append the data to the current item, whatever it is
				if (loTag && !loTag->data())
				{
					// First one, we have to add it to the raw thing
					loTag->set_data(loData);

				}
// 				else
// 				{
// 					// There should only be one data item per tag.
// 					// We ignore this duplicate, or (if there hasn't yet been a tag defined) this orphan data
// 				}

			}
		}
		// When we get here, we need to have the root node closed to be successful
		if (loTag->parent() == loRoot && loTag->is_closed())
		{
			// We're good
			return((u32)loRoot);
		}
		// Syntax error
		return(-2);
	}









//////////
//
// Write the XML data to a file
//
//----------
// Error codes:
//
//		 0				- No error
//		-1				- Unable to open file
//		-2				- Unable to write something
//
/////
	uptr xml_write_file(uptr handle, s8* filename)
	{
		uptr	lnResult;
		CXml*	loRoot;
		CXml*	loTag;


		// Process through the child tags, beginning at the top
		loRoot		= (CXml*)handle;
		loTag		= loRoot->child();
		lnResult	= loTag->save(filename);
		return(lnResult);
	}

	uptr xml_write_file(uptr handle, cs8* filename)
	{
		return(xml_write_file(handle, (s8*)filename));
	}

	uptr xml_write_file(uptr handle, u8* filename)
	{
		return(xml_write_file(handle, (s8*)filename));
	}

	uptr xml_write_file(uptr handle, cu8* filename)
	{
		return(xml_write_file(handle, (s8*)filename));
	}









//////////
//
// Iterate through the specified node to return the specified value
//
//----------
// Input:
//		handle				- handle to XML root node (returned from xml_load functions above
//
//		node				- Pointer to name like "\this(0)\sample(3)" for the XML sample below, which would return "Some data #4 "
//							-				   and "\this(1)\sample(0)" for the XML sample below, which would return "Some data #1 set #2"
//
//							- Supported extensions are:
//									".data"				(default, used when nothing specified, if empty then cdata is used if it's not empty)
//									".cdata"
//									".attrib(n).name"
//									".attrib(n).value"
//
//							- Pointer to name like "\this(1)\sample(3).attrib(0).name" returns "text"
//							- Pointer to name like "\this(1)\sample(3).attrib(0).value" returns "whatever"
//
//		return_value		- Area to store the returned value of data stored in that node (in text form)
//		return_value_length	- Length of the memory block area of return_value
//		iterate				- indicate which node at that level by that name is returned, 0=first
//		data_or_cdata		- 0 for data, 1 for cdata, others invalid
//
/////
	bool xml_access_node_bool(uptr handle, s8* tcNode)
	{
		s8 buffer[32];
		if (xml_access_node(handle, tcNode, &buffer[0], sizeof(buffer)) > 0)
			if (buffer[0] == 'Y' || buffer[0] == 'y' || buffer[0] == '1')
				return(true);

		return(false);
	}

	uptr xml_access_node_integer(uptr handle, s8* tcNode)
	{
		s8 buffer[32];
		if (xml_access_node(handle, tcNode, &buffer[0], sizeof(buffer)) > 0)
			return(atoi(&buffer[0]));

		return(-1);
	}

	f64 xml_access_node_f64(uptr handle, s8* tcNode)
	{
		s8 buffer[32];
		if (xml_access_node(handle, tcNode, &buffer[0], sizeof(buffer)) > 0)
			return(atof(&buffer[0]));

		return(0.0);
	}









	uptr xml_access_node(uptr handle, s8* tcNode, s8* tcReturn_value, u32 tnReturn_value_length)
	{
		u32			/*lnStart, lnLength,*/ lnMaxLength, lnCount;
		CXml*		loRoot;
		CXml*		loTag;
		XmlNode*	loNodeRoot;
		XmlNode*	loNode;


		// Reset all of the tcReturn_value to NULLs
		lnCount = 0;
		while (lnCount < tnReturn_value_length)
		{
			tcReturn_value[lnCount] = 0;
			++lnCount;
		}


		// Determine this level of node we're looking for
//		lnStart		= 0;
//		lnLength	= 0;
		lnMaxLength	= (u32)strlen(tcNode);
		loNodeRoot = iXml_access_node__get_node_segments(tcNode, lnMaxLength);
		if (!loNodeRoot)
		{
			// No node was specified
			return(-1);
		}
		// When we return here, loNode points to the node data for searching through the XMLTag data.
		// This may be confusing, but each node points to a level of data within the XMLTag data, such
		// that the example above of "\this(0)\sample(3)" points to the first <this> tag, and the 4th
		// <sample> tag, which is a child of the found <this> tag.


		// Grab the root and first reference
		loRoot = (CXml*)handle;
		loTag = loRoot->child();


		// Iterate through each node specified until we reach the end, then return the DATA value or CDATA value
 		loNode = loNodeRoot;
		while (loTag && loNode)
		{
			// Iterate through this level to find the first node name
			if (loNode->get_length() == 0 || (loTag->tag() && loTag->tag()->length() == loNode->get_length()))
			{
				// Possible match based on length
				if (loNode->get_length() == 0 || (_memicmp(loTag->tag()->as_s8p(), loNode->get_name(), loNode->get_length()) == 0))
				{
					// It's a match, are we through our iterate yet?
					if (loNode->get_count() >= loNode->get_iterate())
					{
						// We've reached our iterate count, so we're ready to go to the next level (if there is one)
						if (loNode->get_next() && loNode->get_return_type() == XmlNode::none && loNode->get_next()->get_return_type() != XmlNode::none)
						{
							// This is actually the last node, but there's one level below this one to reach the return type
							// See the iXml_access_node__get_node_segments() function to identify why this is
							loNode = loNode->get_next();
						}

						// See what we're returning
						switch (loNode->get_return_type())
						{
							case XmlNode::data:
								// It's time to return the data
								iXml_access_node__copy_data(lnCount, loTag->data(), tcReturn_value, tnReturn_value_length);
								// All done
								delete loNodeRoot;
								return(lnCount);
								break;

							case XmlNode::cdata:
								// It's time to return the cdata
								iXml_access_node__copy_data(lnCount, loTag->cdata(), tcReturn_value, tnReturn_value_length);
								// All done
								delete loNodeRoot;
								return(lnCount);
								break;

							case XmlNode::attrib_name:
							case XmlNode::attrib_value:
								// It's time to return one of the attributes
								// We have to iterate through the attributes to figure out which one they want to return
								if (!loTag->attribute())
								{
									// There are no attributes
									delete loNodeRoot;
									if (tcReturn_value)
										tcReturn_value[0] = 0;
									return(0);
								}

								// There is at least one attribute
								loTag = loTag->attribute();
								if (loNode->get_iterate() == (u32)-1)
								{
									// We are searching for the specified name
									while (loTag)
									{
										if (loNode->get_length() == 0 || (loTag->tag() && loTag->tag()->length() == loNode->get_length()))
										{
											// Possible match based on length
											if (loNode->get_length() == 0 || (_memicmp(loTag->tag()->as_s8p(), loNode->get_name(), loNode->get_length()) == 0))
											{
												// This is the attribute, since we know it by name we are not returning the name type, but always the value
												iXml_access_node__copy_data(lnCount, loTag->data(), tcReturn_value, tnReturn_value_length);
												// All done
												delete loNodeRoot;
												return(lnCount);
											}
										}

										// Move to the next attribute
										loTag = loTag->attribute();
									}
									// If we get here, attribute name was not found
									delete loNodeRoot;
									if (tcReturn_value)
										tcReturn_value[0] = 0;
									return(0);

								}
								else
								{
									// We are iterating through each one to obtain the Nth one
									while (loTag && loNode->get_count() < loNode->get_iterate())
									{
										// We need to go to the next attribute
										loTag = loTag->attribute();
										loNode->set_count(loNode->get_count() + 1);
									}
									if (loTag)
									{
										// We found the position
										switch (loNode->get_return_type())
										{
											case XmlNode::attrib_name:
												// Copy the name
												iXml_access_node__copy_data(lnCount, loTag->tag(), tcReturn_value, tnReturn_value_length);
												break;

											case XmlNode::attrib_value:
												// Copy the value
												iXml_access_node__copy_data(lnCount, loTag->data(), tcReturn_value, tnReturn_value_length);
												break;

										}
										delete loNodeRoot;
										return(lnCount);

									}
									else
									{
										// Attribute requested is out of range
										delete loNodeRoot;
										if (tcReturn_value)
											tcReturn_value[0] = 0;
										return(0);

									}

								}
								break;

							case XmlNode::none:
							default:
								// See if there's anything else after this
								if (!loNode->get_next())
								{
									// This is the last item they're looking for, we found it
									delete loNodeRoot;
									return((u32)loTag);
								}
								// There is another level after this one
								loNode	= loNode->get_next();
								loTag	= loTag->child();
								break;

						}

					}
					else
					{
						// Increase our count by one
						loNode->set_count(loNode->get_count() + 1);
						// Move to the next at this level
						loTag = loTag->next();
						// And continue looking for this matching tag

					}

				}
				else
				{
					// Move to next at this level
					loTag = loTag->next();
				}

			}
			else
			{
				// Move to next at this level
				loTag = loTag->next();

			}

		}
		// When we get here, the tag (or iterate of the tag) wasn't found
		delete loNodeRoot;
		if (tcReturn_value)
			tcReturn_value[0] = 0;

		return(0);
	}
//
//
//
//
//
//
//
//
//
////////////
////
//// Internal support functions for the exposed functions above
////
///////
//	u32 iXml_write_file__write_tag(int tfh, XMLTag* toTag)
//	{
//		while (toTag)
//		{
//			// Write items in this order:
//			//	1)	Tag + attributes
//			//	2)	Data or CDATA
//			//	3)	Child
//			//	4)	Closing tag
//			//	4)	Next
//			if (toTag->get_data() || toTag->get_cdata() || toTag->get_child())
//			{
//				// Write tag
//				if (!iXml_write_file__write_item(tfh, toTag->get_tag()->get_data(), toTag->get_tag()->get_length(), toTag->get_attribute(), (s8*)"<", (s8*)">"))
//				{
//					// An error writing
//					return(-2);
//				}
//
//				// Write data
//				if (toTag->get_data())
//				{
//					// Write data section
//					if (!iXml_write_file__write_item(tfh, toTag->get_data()->get_data(), toTag->get_data()->get_length(), NULL, (s8*)"", (s8*)""))
//					{
//						// An error writing
//						return(-2);
//					}
//
//				}
//
//				// Write CDATA
//				if (toTag->get_cdata())
//				{
//					// Write CDATA section
//					if (!iXml_write_file__write_item(tfh, toTag->get_cdata()->get_data(), toTag->get_cdata()->get_length(), NULL, (s8*)"<![CDATA[", (s8*)"]]>"))
//					{
//						// An error writing
//						return(-2);
//					}
//
//				}
//
//				// Write child entries
//				if (toTag->get_child())
//				{
//					// Write child portion
//					iXml_write_file__write_tag(tfh, toTag->get_child());
//				}
//
//				// Write closing tag
//				if (!iXml_write_file__write_item(tfh, toTag->get_tag()->get_data(), toTag->get_tag()->get_length(), NULL, (s8*)"</", (s8*)">"))
//				{
//					// An error writing
//					return(-2);
//				}
//
//			}
//			else
//			{
//				// It's just a single tag
//				// It should have no children, no data, no cdata, possibly only attributes
//				if (!iXml_write_file__write_item(tfh, toTag->get_tag()->get_data(), toTag->get_tag()->get_length(), toTag->get_attribute(), (s8*)"<", (s8*)"/>"))
//				{
//					// An error writing
//					return(-2);
//				}
//
//			}
//
//			// Move to next item
//			toTag = toTag->get_next();
//		}
//		// No error
//		return(0);
//	}
//
//
//	// Writes data like "<" + tcData + ">"
//	bool iXml_write_file__write_item(int tfh, s8* tcData, u32 tnLength, XMLTag* toAttribute, s8* tcOpenCharacters, s8* tcCloseCharacters)
//	{
//		u32 numread1, numread2, numread3;
//
//
//		// See if there's anything
//		if (tcData && tnLength != 0)
//		{
//			// Write this data
//			numread1 = write(tfh, tcOpenCharacters, strlen(tcOpenCharacters));
//			numread2 = write(tfh, tcData, tnLength);
//			if (numread1 != strlen(tcOpenCharacters) || numread2 != tnLength)
//			{
//				// Some error writing
//				return(false);
//			}
//
//
//			// Write any attributes
//			iXml_write_file__write_attribute(tfh, toAttribute);
//
//
//			// Close the tag
//			numread3 = write(tfh, tcCloseCharacters, strlen(tcCloseCharacters));
//			if (numread3 != strlen(tcCloseCharacters))
//			{
//				// Some error writing
//				return(false);
//			}
//
//			// We're good
//			return(true);
//		}
//		// Nothing to write
//		return(true);
//	}
//
//
//	bool iXml_write_file__write_attribute(int tfh, XMLTag* toAttribute)
//	{
//		u32 numread1, numread2, numread3, numread4, numread5;
//
//
//		// Write any attributes
//		while (toAttribute)
//		{
//			if (toAttribute->get_tag())
//			{
//				// There is a tag here
//				if (toAttribute->get_data())
//				{
//					// And data, we're good to go
//					numread1 = write(tfh, " ", 1);
//					numread2 = write(tfh, toAttribute->get_tag()->get_data(), toAttribute->get_tag()->get_length());
//					numread3 = write(tfh, "='", 2);
//					numread4 = write(tfh, toAttribute->get_data()->get_data(), toAttribute->get_data()->get_length());
//					numread5 = write(tfh, "'", 1);
//					if (numread1 != 1 || numread3 != 2 || numread5 != 1 ||
//						numread2 != toAttribute->get_tag()->get_length() ||
//						numread4 != toAttribute->get_data()->get_length())
//					{
//						// Some error writing
//						return(false);
//					}
//					// We're good, tag is written
//				}
//			}
//
//			// Move to next attribute
//			toAttribute = toAttribute->get_attribute();
//		}
//		// No error
//		return(true);
//	}


//////////
//
// Skip past white spaces, tabs, carriage returns and line feeds
//
/////
	void iXml_load__skip_white_spaces(s8* buffer, u32 tnOffset, u32& tnThis, u32 tnLength)
	{
		while (tnOffset + tnThis < tnLength)
		{
			switch (buffer[tnOffset + tnThis])
			{
				case 32:
				case  9:
				case 10:
				case 13:
					// It's a whitespace
					++tnThis;
					break;

				default:
					// It's some valid character
					return;
			}
		}
		// When we get here, we've reached the maximum length.
		return;
	}


//////////
//
// Load attributes
//
/////
	void iXml_load__attributes(CXml* toTag, s8* buffer, u32 tnOffset, u32& tnThis, u32 tnLength)
	{
		u32			lnCountName, lnCount;
		// Attribute tag, name and value
		CXml*		loTag;
		CXml*		loNew;
		XmlData*	loName;			// Attribute name, such as "attribute" in <tag attribute='sample'>
		XmlData*	loValue;		// Attribute data, such as "sample" in <tag attribute='sample'>
		s8			lcQuoteChar;



		// Store the called tag as our starting tag
		// Note:  This tag is either the <tag> object, or is one of the previous attributes
		// Note:  Regardless, we store a new XMLTag() and store m_tag as the attribute name, and m_data as the attribute data
		loTag = toTag;


		// When called, we're sitting at the start of the attribute name
		loName = new XmlData();
		loName->set_data(&buffer[tnOffset + tnThis]);


		// Find out how long this name is
		lnCountName = 0;
		while (tnOffset + tnThis < tnLength)
		{
			// Store the length (in case this is the one)
			loName->set_length(lnCountName);

			// See where we are in the name='value' thing
			switch (buffer[tnOffset + tnThis])
			{
				case 32:/*space*/
					// We've reached a space between two attributes (most likely)

					// Skip repeated spaces
					iXml_load__skip_white_spaces(buffer, tnOffset, tnThis, tnLength);

					// Right now, we should be sitting on an equal sign
					if (buffer[tnOffset + tnThis] != '=')
					{
						// Syntax error
						delete loName;

						// Skip everything else until we reach the closing >
						while (tnOffset + tnThis < tnLength)
						{
							if (buffer[tnOffset + tnThis] == '>')
							{
								// We've reached the end
							}
							// Move to next character
							++tnThis;
						}
						// When we get here, we're at the end of the XML file
						return;
					}
					// Falls through to the same code as the equal sign
				case '=':
					// Skip past equal sign
					if (tnOffset + tnThis + 1 >= tnLength)
					{
						// We've reached the end of the XML file
						delete loName;
						return;
					}
					++tnThis;

					// Skip repeated spaces
					iXml_load__skip_white_spaces(buffer, tnOffset, tnThis, tnLength);

					// Right now, we must be sitting on the quote character
					if (buffer[tnOffset + tnThis] != 39 &&	/* Single-quote */
						buffer[tnOffset + tnThis] != 34)	/* Double-quote */
					{
						// Syntax error
						delete loName;

						// Skip everything else until we reach the closing >
						while (tnOffset + tnThis < tnLength)
						{
							if (buffer[tnOffset + tnThis] == '>')
							{
								// We've reached the end
							}
							// Move to next character
							++tnThis;
						}
						// When we get here, we're at the end of the XML file
						return;
					}

					// We allow single- or double-quote characters, but they must match on both sides of the attribute value
					lcQuoteChar = buffer[tnOffset + tnThis];
					if (tnOffset + tnThis + 1 >= tnLength)
					{
						// We've reached the end of the XML file
						delete loName;
						return;
					}
					// Move past quote character
					++tnThis;

					// Next, look for the closing quote character and store all data between as this name's value
					loValue = new XmlData();
					loValue->set_data(&buffer[tnOffset + tnThis]);

					// Iterate until we find closing quote character (or a closing > character, or reach the end of the XML file)
					lnCount = 0;		// Holds length of the item found between starting point and ending point
					while (tnOffset + tnThis < tnLength)
					{
						if (buffer[tnOffset + tnThis] == lcQuoteChar)
						{
							// We've reached our quote character
							// This is the end of this attribute, but may also be the end of the tag

							// Store the length
							loValue->set_length(lnCount);

							// Update the tag
							// Must be added to the chain, which means this is at least the second attribute found
							loNew = new CXml();
							loNew->set_tag(loName);
							loNew->set_data(loValue);
							loNew->set_parent(loTag);
							loTag->set_attribute(loNew);

							// We're sitting on closing quote
							// Move to whatever the next character is
							if (tnOffset + tnThis + 1 >= tnLength)
							{
								// We've reached the end of the XML file
								return;
							}
							++tnThis;
							// Right now, we're on whatever is after the closing quote, which could be white spaces

							// Skip repeated spaces
							iXml_load__skip_white_spaces(buffer, tnOffset, tnThis, tnLength);

							// Test the real character we're on
							// If it's a > or /, then we're done
							switch (buffer[tnOffset + tnThis])
							{
								case '>':
								case '/':
									// We're done, the closing character will be returned below
									break;

								default:
									// More attributes follow this one, load them from here, append onto the chain
									iXml_load__attributes(loNew, buffer, tnOffset, tnThis, tnLength);
									break;
							}
							// When we get here, we've loaded all the attributes
							// Return the current closing character
							return;

						}
						else if (buffer[tnOffset + tnThis] =='>')
						{
							// We're still within the attribute's value
							// We've reached the end of the tag, which means a syntax error because there was no closing quote character.
							// As such, ignore the value quantity
							delete loValue;
							// Right now, tnOffset + tnThis is sitting on the closing character for the attribute set
							// The calling algorithm will then close the appropriate tag
							return;
						}

						// Still scanning the attribute text
						++tnThis;
						++lnCount;
					}
					// When we get here, we've reached the end of the XML file, which is a syntax error
					delete loValue;
					return;

				default:
					// Move to the next character in the name
					++tnThis;
					++lnCountName;
					break;
			}
		}
	}


	XmlNode* iXml_access_node__get_node_segments(s8* tcNode, u32 tnMaxLength)
	{
		XmlNode* loNodeRoot = NULL;
		XmlNode* loNode = NULL;
		XmlNode* loNew;
		u32 lnStart, lnLength, lnN, lnType, lnNodeStart, lnNodeLength;
		bool lbMustBeEnd;


		// Make sure there's something to search
		if (tcNode && tcNode[0] != 0)
		{
//////////
//
// The format we look for at each node level is:
//
//		(optional)  \			// Leading \ character is optional, but syntactically identifies the root.  If missing, root is still assumed.
//		(optional)	tag_name	// If no (n) is specified, this value MUST be specified
//		(optional)	(n)			// If no tag_name is specified, this one must be.  If tag_name specified and (n) is not, (0) is assumed (first instance)
//
//----------
//
// For the last node in the path/tree/branch, one of these optional parameters are available.
// By default ".data" is assumed, and when data is returned at that level by the code above,
// if there is no ".data" data, then if there is ".cdata" data, the CDATA is returned:
//
//		(optional)	.data
//					.cdata
//					.attrib(n).name		&& if .attrib(n) is specified, then .name or .value IS required
//					.attrib(n).value
//
//----------
//
// Examples:
//
//		\this(0)\level(0)\data(3).attrib(0).name
//		\this(1)\field(2).attrib(1).name
//		\this(1)\field(2).attrib(1).value
//
/////
			// Begin at the beginning
			lnStart		= 0;
			lnLength	= 0;
			if (tcNode[lnStart] == '\\')
			{
				// Skip past the leading \ character, which is optional
				++lnStart;
			}


			// Iterate until we find the next ( or \ or . or we reach the end of the input
			lnLength	= 0;
			lbMustBeEnd	= false;
			while (!lbMustBeEnd && lnStart + lnLength < tnMaxLength)
			{
				switch (tcNode[lnStart + lnLength])
				{
					case '\\':
// \ indicator, end of current node name, beginning of next
						if (lnLength == 0)
						{
							// Syntax error
							lbMustBeEnd = true;
							break;
						}

						// Store the node
						loNew = new XmlNode();
						loNew->set_name(tcNode + lnStart, lnLength);
						if (loNode && loNodeRoot)
						{
							// Append it to the chain
							loNode->set_next(loNew);
							loNode = loNew;

						}
						else
						{
							// First one
							loNode		= loNew;
							loNodeRoot	= loNew;		// Store for the return value
						}

						// Reset our variables for the next group (if any)
						lnStart += lnLength + 1;
						lnLength = 0;
						break;


					case '(':
// (n) indicator for the tag
						// The name is currently maxed out, so we can create the new node
						// We've reached the beginning of the next node
						if (lnLength == 0)
						{
							// Syntax error
							lbMustBeEnd = true;
							break;
						}

						// Store variables to create the node below
						lnNodeStart = lnStart;
						lnNodeLength = lnLength;
						// We don't create the XMLNode yet, because there could be syntax errors

						// Now, see what our iterator value is
						++lnLength;
						if (lnStart + lnLength >= tnMaxLength)
						{
							// Syntax error, must be at least ".attrib.name" or ".attrib.value"
							lbMustBeEnd = true;
							break;

						}
						// Grab the (n) value here
						lnN = iXml_access_node__store_n(tcNode, lnStart, lnLength, tnMaxLength);
						// Right now, tcNode[lnStart + lnLength] should be pointing to the ( character
						if (lnStart + lnLength >= tnMaxLength)
						{
							// Syntax error, we reached the end before the closing ) character
							lbMustBeEnd = true;
							break;
						}
						// If we get here, then there is a chance it's the closing ) character
						if (tcNode[lnStart + lnLength] != ')')
						{
							// Syntax error
							lbMustBeEnd = true;
							break;

						}
						// We're good, move past the closing ) character
						++lnLength;

						// Store this one
						loNew = new XmlNode();
						loNew->set_name(tcNode + lnNodeStart, lnNodeLength);
						if (loNodeRoot)
						{
							// Append it to the chain
							loNode->set_next(loNew);
							loNode = loNew;

						}
						else
						{
							// First one
							loNode		= loNew;
							loNodeRoot	= loNew;		// Store for the return value
						}
						// There should be something after this
						loNode->set_iterate(lnN);
						lnStart += lnLength;
						lnLength = 0;
						if (lnStart + lnLength < tnMaxLength)
						{
							if (tcNode[lnStart + lnLength] == '\\')
							{
								// Skip past this divider character
								++lnStart;
							}
							// else, it could be a .data or something, so we leave those for the parser
						}
						// We're ready for the next thing
						break;


					case '.':
// The last tag will be .data, .cdata, .attrib(n).name or .attrib(n).value

						// See if it's ".data"
						if (lnStart + lnLength + 5 <= tnMaxLength)
						{
							if (_memicmp(&tcNode[lnStart + lnLength], (s8*)".data", 5) == 0)
							{
								// This is a match
								loNew = new XmlNode();
								loNew->set_name(tcNode + lnStart, 5);
								if (loNodeRoot)
								{
									// Append it to the chain
									loNode->set_next(loNew);
									loNode = loNew;

								}
								else
								{
									// First one
									loNode		= loNew;
									loNodeRoot	= loNew;		// Store for the return value
								}
								loNode->set_return_type(XmlNode::data);
								lbMustBeEnd = true;
								break;
							}
						}

						// See if it's ".cdata"
						if (lnStart + lnLength + 6 <= tnMaxLength)
						{
							if (_memicmp(&tcNode[lnStart + lnLength], (s8*)".cdata", 6) == 0)
							{
								// This is a match
								loNew = new XmlNode();
								loNew->set_name(tcNode + lnStart, 6);
								if (loNodeRoot)
								{
									// Append it to the chain
									loNode->set_next(loNew);
									loNode = loNew;

								}
								else
								{
									// First one
									loNode		= loNew;
									loNodeRoot	= loNew;		// Store for the return value
								}
								loNode->set_return_type(XmlNode::cdata);
								lbMustBeEnd = true;
								break;
							}
						}

						// See if it's ".attrib"
						if (lnStart + lnLength + 7 <= tnMaxLength)
						{
							if (_memicmp(&tcNode[lnStart + lnLength], (s8*)".attrib", 7) == 0)
							{
								// Store variables to create the node below
								lnNodeStart		= lnStart + lnLength;
								lnNodeLength	= 7;
								// We don't create the XMLNode yet, because there could be syntax errors

								lnLength += 7;
								if (tcNode[lnStart + lnLength] == '(')
								{
									// They have specified an (n) value, or possibly an attribute name
									++lnLength;
									if (tcNode[lnStart + lnLength] >= '0' && tcNode[lnStart + lnLength] <= '9')
									{
										// Attribute by number or iterate
										// Grab the (n) value here
										lnN = iXml_access_node__store_n(tcNode, lnStart, lnLength, tnMaxLength);
										// Right now, tcNode[lnStart + lnLength] should be pointing to the ( character
										if (lnStart + lnLength >= tnMaxLength)
										{
											// Syntax error, we reached the end before the closing ) character
											lbMustBeEnd = true;
											break;
										}
										// If we get here, then there is a chance it's the closing ) character
										if (tcNode[lnStart + lnLength] != ')')
										{
											// Syntax error
											lbMustBeEnd = true;
											break;

										}

									}
									else
									{
										// Attribute by name (of if they specified no name they want the first (possibly only) attribute)
										lnNodeStart		= lnStart + lnLength;
										lnNodeLength	= 0;
										while (lnNodeStart + lnNodeLength <= tnMaxLength && tcNode[lnNodeStart + lnNodeLength] != ')')
										{
											// Move to the next character
											++lnNodeLength;
										}

										// When we get here, we have the length of the name
										// Note:  If the name is zero characters, then they want the first attribute
										lnN = -1;
										lnLength += lnNodeLength;

									}
									// We're good, move past the closing ) character
									++lnLength;

								}
								else
								{
									// We assume (n) = (0)
									lnN = 0;

								}

								if (_memicmp(&tcNode[lnStart + lnLength], (s8*)".name", 5) == 0)
								{
									// A match
									lnType = XmlNode::attrib_name;
									lnLength += 5;

								}
								else if (lnStart + lnLength + 6 <= tnMaxLength)
								{
									if (_memicmp(&tcNode[lnStart + lnLength], (s8*)".value", 6) == 0)
									{
										// A match
										lnType = XmlNode::attrib_value;
										lnLength += 6;

									}
									else
									{
										// Not a match of the only two options, syntax error
										lbMustBeEnd = true;
										break;

									}

								}
								else
								{
									// Syntax error, because it wasn't .name and it's not at least 6 characters long for .value
									lbMustBeEnd = true;
									break;

								}
								// When we get here, we've found our matches, and our (n) value

								// Store the node
								loNew = new XmlNode();
								loNew->set_name(tcNode + lnNodeStart, lnNodeLength);
								if (loNodeRoot)
								{
									// Append it to the chain
									loNode->set_next(loNew);
									loNode = loNew;

								}
								else
								{
									// First one
									loNode		= loNew;
									loNodeRoot	= loNew;		// Store for the return value
								}
								loNew->set_iterate(lnN);
								loNew->set_return_type(lnType);
								// This is the last thing it could be, we force the ending
								lbMustBeEnd = true;
								break;
							}
							else
							{
								// Syntax error, unrecognized . thing
								lbMustBeEnd = true;
								break;

							}
						}
						break;

					default:
						// Move to next position
						++lnLength;
						break;
				}
				// When we get here, we're at the next character to test, or at the end of the string
			}
			// When we get here, we've reached the end of the string

			// See if there's the last node that hasn't yet been stored
			if (!lbMustBeEnd && lnLength != 0)
			{
				// Store the last node
				loNew = new XmlNode();
				loNew->set_name(tcNode + lnStart, lnLength - 1);
				if (loNodeRoot)
				{
					// Append it to the chain
					loNode->set_next(loNew);

				}
				else
				{
					// First one
					loNode		= loNew;
					loNodeRoot	= loNew;		// Store for the return value
				}
			}
			// All done!
		}

		// When we get here, we've reached the end
		return(loNodeRoot);
	}


	u32 iXml_access_node__store_n(s8* tcNode, u32 tnStart, u32& tnLength, u32 tnMaxLength)
	{
		u32 lnN;


		// Scan through the digits, obtaining the offset
		lnN = 0;
		while (       tnStart + tnLength	<	tnMaxLength	&&
			   tcNode[tnStart + tnLength]	>=	'0'			&&
			   tcNode[tnStart + tnLength]	<=	'9')
		{
			// Multiply existing value by 10, and add in this digit
			lnN = (lnN * 10) + (u32)(tcNode[tnStart + tnLength] - '0');

			// Move to the next digit
			++tnLength;
		}

		// When we get here, we have our value
		return(lnN);
	}


	void iXml_access_node__copy_data(u32& tnCount, XmlData* toData, s8* tcReturn_value, u32 tnReturn_value_length)
	{
		// Copy everything
		tnCount = 0;

		// See if we can copy anything
		if (toData && tcReturn_value)
		{
			while (tnCount < toData->length() &&
				tnCount < tnReturn_value_length)
			{
				// Copy the next character
				tcReturn_value[tnCount] = toData->as_s8p()[tnCount];

				// Move to the next position
				++tnCount;
			}
			// When we get here, done copying
		}

		// NULL-terminate if possible
		if (tcReturn_value && tnCount < tnReturn_value_length)
		{
			tcReturn_value[tnCount] = 0;
		}
	}
