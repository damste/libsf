//////////
//
// /libsf/source/vjr/source/datum/datum.cpp
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
// Version 0.58
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Nov.27.2014
//////
// Change log:
//     Nov.27.2014 - Initial creation
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
//////
//  _____          _
// |  __ \        | |
// | |  | |  __ _ | |_  _   _  _ __ ___
// | |  | | / _` || __|| | | || '_ ` _ \
// | |__| || (_| || |_ | |_| || | | | | |
// |_____/  \__,_| \__| \__,_||_| |_| |_|
// Datum --- Data w/allocation and length
//
//////////




//////////
//
// Datum storage
//
//////
	void iDatum_allocateSpace(SDatum* datum, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum)
		{
			if (datum->data_s8 && datum->length != dataLength)
			{
				// Release anything that's already there
				iiDatum_delete(datum);
			}

			// Allocate the space
			datum->data_s8 = (s8*)malloc(max(dataLength, 1) + 1);

			// Set the length
			datum->length = dataLength;

			// Initialize
			if (datum->data_s8 && dataLength)
				memset(datum->data_s8, 0, dataLength);

			// NULL-terminate
			datum->data_s8[max(dataLength, 1)] = 0;
		}
	}

	SDatum* iDatum_allocate(cs8* data, s32 dataLength)
	{
		return(iDatum_allocate((u8*)data, dataLength));
	}

	SDatum* iDatum_allocate(s8* data, s32 dataLength)
	{
		return(iDatum_allocate((u8*)data, dataLength));
	}

	SDatum* iDatum_allocate(cu8* data, s32 dataLength)
	{
		return(iDatum_allocate((u8*)data, dataLength));
	}

	SDatum* iDatum_allocate(u8* data, s32 dataLength)
	{
		SDatum* datumNew;


		// Allocate our new datum
		datumNew = (SDatum*)malloc(sizeof(SDatum));
		if (datumNew)
		{
			// Initialize
			memset(datumNew, 0, sizeof(SDatum));

			// Copy over the content
			if (data)
			{
				// We may need to set the length
				if (dataLength < 0)
					dataLength = (s32)strlen((s8*)data);

				// Initialize
				memset(datumNew, 0, sizeof(SDatum));

				// Populate
				iDatum_duplicate(datumNew, data, dataLength);
			}
		}

		// Indicate our status
		return(datumNew);
	}

	void iDatum_duplicate(SDatum* datum, u8* data, s32 dataLength)
	{
		// Make sure our environment is sane
		if (datum && data)
		{
			// We may need to set the length
			if (dataLength < 0)
				dataLength = (s32)strlen((s8*)data);

			// Release anything that's already there
			iiDatum_delete(datum);

			// Store the new data
			// Allocate one extra byte for a trailing NULL
			datum->data_s8 = (s8*)malloc(max(dataLength, 1) + 1);

			// Copy over if we were successful
			if (datum->data_s8 && dataLength > 0)
				memcpy(datum->data_s8, data, dataLength);

			// Store the new length
			datum->length = dataLength;
			datum->data_s8[max(dataLength, 1)] = 0;
		}
	}

	void iDatum_duplicate(SDatum* datum, s8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datum, cu8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datum, cs8* data, s32 dataLength)
	{
		iDatum_duplicate(datum, (u8*)data, dataLength);
	}

	void iDatum_duplicate(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc && datumSrc->data_u8)
			iDatum_duplicate(datumDst, datumSrc->data_u8, datumSrc->length);
	}

	void iDatum_duplicate_byRef(SDatum* datumDst, SDatum* datumSrc)
	{
		// Make sure our environment is sane
		if (datumDst && datumSrc)
		{
			// Copy the content as a reference
			datumDst->_data		= datumSrc->_data;
			datumDst->length	= datumSrc->length;
		}
	}

	SDatum* iDatum_duplicate(SDatum* datum)
	{
		// Duplicate if possible
		if (datum && datum->_data && datum->length > 0)
			return(iDatum_allocate(datum->data_s8, datum->length));

		// If we get here, invalid
		return(NULL);
	}

#ifdef _SCOMP_DEFINED
	void iDatum_duplicate_fromComp(SDatum* datum, SComp* comp)
	{
		// Make sure our environment is sane
		if (datum && comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data_cs8 && comp->length != 0)
			iDatum_duplicate(datum, comp->line->sourceCode->data_cs8 + comp->start, comp->length);
	}

	void iiDatum_duplicate_fromComp(SDatum* datum, SComp* comp)
	{
		iDatum_duplicate(datum, comp->line->sourceCode->data_cs8 + comp->start, comp->length);
	}

	SDatum* iDatum_populate_fromComp(SDatum* datum, SComp* comp)
	{
		// Make sure the datum and component are valid
		if (datum && comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data_s8 && comp->line->sourceCode->length >= comp->start + comp->length)
		{
			datum->data_s8	= comp->line->sourceCode->data_s8 + comp->start;
			datum->length	= comp->length;
		}

		// Pass-thru
		return(datum);
	}
#endif

	s32 iDatum_getAs_s32(SDatum* datum)
	{
		return(((datum && datum->_data && datum->length > 1) ? atoi(datum->data_s8) : 0));
	}

	s64 iDatum_getAs_s64(SDatum* datum)
	{
		return(((datum && datum->_data && datum->length > 1) ? _atoi64(datum->data_s8) : 0));
	}

	// Set everything to the indicated character
	s32 iDatum_setAll(SDatum* datum, u8 c)
	{
		if (datum && datum->_data && datum->length > 0)
		{
			memset(datum->data_s8, c, datum->length);
			return(datum->length);
		}

		// If we get here, invalid
		return(0);
	}

	bool iDatum_resize(SDatum* datum, s32 newDataLength)
	{
		s8* ptr;


		// Make sure our environment is sane
		if (datum && newDataLength != 0)
		{
			if (datum->length == newDataLength)
				return(true);		// It's already the same length

			// Allocate our new block
			ptr = (s8*)malloc(newDataLength + 1);
			if (ptr)
			{
				// Copy everything that will fit
				memcpy(ptr, datum->data_s8, min(newDataLength, datum->length));

				// Fill the remainder with NULLs if any
				if (newDataLength > datum->length)
					memset(ptr + datum->length, 0, newDataLength - datum->length);

				// Null-terminate
				ptr[newDataLength] = 0;

				// Delete the old data
				if (datum->data_s8)
					free(datum->data_s8);

				// And populate with the new data
				datum->data_s8	= ptr;
				datum->length	= newDataLength;

				// All done
				return(true);

			} else {
				// Failure
				return(false);
			}

		} else {
			// No data to work with
			return(false);
		}
	}

	// Returns -1, 0, or 1 (indicating left is less than, equal to, or greater than right)
	s32 iDatum_compare(SDatum* datumLeft, SDatum* datumRight)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;

		// Make sure our environment is sane
		if (datumLeft && datumLeft->_data && datumLeft->length != 0 && datumRight && datumRight->_data && datumRight->length > 0)
		{
			// Do a standard compare
			lnResult = _memicmp(datumLeft->data_s8, datumRight->data_s8, min(datumLeft->length, datumRight->length));
		}

		// Indicate our result
		return(lnResult);
	}

	s32 iDatum_compare(SDatum* datumLeft, s8* data, s32 dataLength)
	{
		s32 lnResult;


		// Default to invalid data
		lnResult = -2;

		// Make sure our environment is sane
		if (datumLeft && datumLeft->_data && datumLeft->length != 0 && data)
		{
			// Make sure our length is set
			if (dataLength < 0)
				dataLength = (s32)strlen(data);

			// Do a standard compare
			lnResult = _memicmp(datumLeft->data_s8, data, min(datumLeft->length, dataLength));
		}

		// Indicate our result
		return(lnResult);
	}

	s32 iDatum_compare(SDatum* datumLeft, cs8* data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	s32 iDatum_compare(SDatum* datumLeft, u8*  data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	s32 iDatum_compare(SDatum* datumLeft, cu8* data, s32 dataLength)
	{
		return(iDatum_compare(datumLeft, (s8*)data, dataLength));
	}

	void iDatum_delete(SDatum** datum)
	{
		if (datum)
		{
			// Delete and reset our pointer
			iDatum_delete(*datum, true);
			*datum = NULL;
		}
	}

	void iDatum_delete(SDatum* datum, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (datum)
		{
			// Delete the content
			iiDatum_delete(datum);

			// Delete self if need be
			if (tlDeleteSelf)
				free(datum);
		}
	}

	void iiDatum_delete(SDatum* datum)
	{
		// Make sure our environment is sane
		if (datum->data_s8)
		{
			free(datum->data_s8);
			datum->data_s8 = NULL;
		}

		// Reset the length to zero
		datum->length = 0;
	}




//////////
//
// Combined properties
//
//////
#ifdef _SPROPERTY_DEFINED
#ifdef _SCOMP_DEFINED
	SProperty* iProperty_allocateAs_character_fromComp(SComp* name, SComp* value, s32 tnOverrideNameLength, s32 tnOverrideValueLength)
	{
		s32 lnNameLength, lnValueLength;


		// Make sure our environment is sane
		if (name && value && name->line && name->line->sourceCode && name->line->sourceCode->_data && value->line && value->line->sourceCode && value->line->sourceCode->_data)
		{
			// Get the names
			lnNameLength	= ((tnOverrideNameLength > 0)	? tnOverrideNameLength	: name->length);
			lnValueLength	= ((tnOverrideValueLength > 0)	? tnOverrideValueLength	: value->length);

			// Create the property
			return(iProperty_allocateAs_character(name->line->sourceCode->data_cu8, lnNameLength, value->line->sourceCode->data_cu8, lnValueLength));

		} else {
			// Failure
			return(NULL);
		}
	}
#endif

	SProperty* iProperty_allocateAs_character(cu8* tcName, s32 tnNameLength, cu8* tcValue, s32 tnValueLength)
	{
		SDatum*		name;
#ifdef _SVARIABLE_DEFINED
		SVariable*	value;
#endif
		SDatum*		value_datum;
		SProperty*	p;


		// Make sure our environment is sane
		p = NULL;
		if (tcName)
		{
			// Allocate a name
			name = iDatum_allocate(tcName, tnNameLength);
			if (name)
			{
				// Allocate the value
#ifdef _SVARIABLE_DEFINED
				// Allocate as a variable
				value = iVariable_createAndPopulate_byText(iiVariable_getType_character(), tcValue, tnValueLength, false);
				if (value)
				{
					// Allocate a property
					p = iiProperty_allocate(name, value);
					if (p)
					{
						// Both were allocated
						p->name_allocated	= true;
						p->value_allocated	= true;

					} else {
						// Failure on creating the property
						iDatum_delete(&name);
						iVariable_delete(&value);
					}
				}
#endif
				// Allocate as a datum
				value_datum = iDatum_allocate(tcValue, tnValueLength);
				if (value_datum)
				{
					// Allocate a property
					p = iiProperty_allocate(name, NULL, value_datum);
					if (p)
					{
						// Both were allocated
						p->name_allocated = true;

					} else {
						// Failure on creating the property
						iDatum_delete(&name);
						iDatum_delete(&value_datum);
					}

				} else {
					// Failure on creating the variable
					iDatum_delete(&name);
				}
			}
		}

		// Indicate our property
		return(p);
	}

	SProperty* iProperty_allocateAs_s32(cu8* tcName, s32 tnNameLength, s32 tnValue)
	{
		SDatum*		d;
		SProperty*	p;


		// Make sure our environment is sane
		p = NULL;
		if (tcName)
		{
			// Allocate a name
			d = iDatum_allocate(tcName, tnNameLength);
			if (d)
			{
				// Allocate a property
				p = iProperty_allocateAs_s32(d, tnValue);
				if (p)
					p->name_allocated = true;
			}
		}

		// Indicate our property
		return(p);
	}

	SProperty* iProperty_allocateAs_s32(SDatum* name, s32 tnValue)
	{
		SProperty*	p;
#ifdef _SVARIABLE_DEFINED
		SVariable*	value;
#endif
		SDatum*		value_datum;
		s8			buffer[32];


		// Make sure our environment is sane
		p = NULL;
		if (name)
		{
			// Store the value
			sprintf(buffer, "%d", tnValue);
			value_datum	= iDatum_allocate(buffer);
			if (value_datum)
			{
				// Create the property
				p = iiProperty_allocate(name, NULL, value_datum);
			}

			// Create a variable
#ifdef _SVARIABLE_DEFINED
			value = iVariable_createAndPopulate_byText(iiVariable_getType_s32(), (cs8*)&tnValue, 4, false);
			if (value)
			{
				// Create the property
				p = iiProperty_allocate(name, value);
				if (p)
					p->value_allocated = true;

			}
#endif
		}

		// Indicate our property
		return(p);
	}

	SProperty* iiProperty_allocate(SDatum* name, SVariable* value, SDatum* value_datum)
	{
		SProperty*	p;


		// Allocate a new one
		p = (SProperty*)malloc(sizeof(SProperty));
		if (p)
		{
			// Pass-thru whatever they send, NULL or otherwise
			p->name			= name;
			p->value		= value;
			p->value_datum	= value_datum;
		}

		// Indicate our new property
		return(p);
	}

	void iProperty_delete(SProperty** p)
	{
		SProperty* t;


		// Make sure our environment is sane
		if (p)
		{
			t	= *p;
			*p	= NULL;
			iProperty_delete(t, true);
		}
	}

	SProperty* iProperty_delete(SProperty* p, bool tlDeleteSelf)
	{
		// Make sure our environment is sane
		if (p)
		{
			// Clean up the name and value
			if (p->name  && p->name_allocated)
				iDatum_delete(&p->name);

			// If it's a datum, delete it
			if (p->value_datum)
			{
				// value_datum's are always allocated
				iDatum_delete(&p->value_datum);
			}

#ifdef _SVARIABLE_DEFINED
			if (p->value && p->value_allocated)
			{
				// Delete the variable
				iVariable_delete(&p->value);
			}
#endif

			// Delete self
			if (tlDeleteSelf)
				free(p);
		}

		// Pass-thru
		return(p);
	}

	// Called to iterate through every property and return its value, from a list like this:
	//		propName1 = value1			// Sends [propName1] and [value1] to cb->propAndValue_func()
	//		prop2 = "text2"				// Sends [prop2] and ["text2"] to cb->propAndValue_func()
	//		property3 = val3			// Sends [property3] and [val3] to cb->propAndValue_func()
	//
	// Returns the number of properties dispatched into cb->propAndValue_func()
	s32 iProperty_iterate(SDatumCallback* cb, SDatum* properties)
	{
		s8		c;
		s32		lnI, lnLength, lnProperties;


		// Make sure our environment is sane
		if (properties && properties->_data && properties->length > 0 && cb)
		{
			// Iterate through line after line looking for:
			//
			//		[x][=]["]...["]
			//		[x][=][y]
			//
			// (1) Sets prop to [x], and value to ["..."] or [y]
			// (2) Whitespaces before and after [x] are ignored
			// (3) Whitespaces after [=] are ignored
			// (4) Everything after ["..."] or [y] is ignored to CR/LF
			for (lnI = 0, lnProperties = 0; lnI < properties->length; )
			{
				//////////
				// Prop
				//////
					//////////
					// Locate the property (first non-whitespace character)
					//////
						// Skip past whitespaces
						while (((c = properties->data_s8[lnI]) == 32 || c == 9) && lnI < properties->length)
							++lnI;

						// Did we go too far?
						if (lnI >= properties->length)
							return(lnProperties);		// Yes

						// Are we at the end of the line?
						if (c == 13 || c == 10)
							goto skip_to_next_line;

						// Mark the start
						cb->prop.data_s8 = properties->data_s8 + lnI;


					//////////
					// Find out how long the prop is
					//////
						for (lnLength = 0; lnI + lnLength < properties->length; lnLength++)
						{
							// Continue until we reach the equal sign
							if ((c = properties->data_s8[lnI + lnLength]) == '=')
								break;	// We're done

							// Have we reached the end of line?
							if (c == 13 || c == 10)
							{
								// This was an invalid line
								lnI += lnLength;
								goto skip_to_next_line;
							}
						}

						// Did we go too far?
						if (lnI >= properties->length)
							return(lnProperties);		// Yes

						// Store the length
						cb->prop.length = lnLength;

						// Move past it
						lnI += lnLength;


				//////////
				// Equal sign
				//////
					// Skip forward until we hit =, or CR/LF
					while ((c = properties->data_s8[lnI]) != 13 && c != 10 && c != '=' && lnI < properties->length)
						++lnI;

					// Did we go too far?
					if (lnI >= properties->length)
						return(lnProperties);		// Yes

					// Are we at the end of the line?
					if (c == 13 || c == 10)
						goto skip_to_next_line;

					// Skip past it
					++lnI;


				//////////
				// Value
				//////
					//////////
					// Find out where it starts
					//////
						// Skip past whitespaces
						while (((c = properties->data_s8[lnI]) == 32 || c == 9) && lnI < properties->length)
							++lnI;

						// Did we go too far?
						if (lnI >= properties->length)
							return(lnProperties);		// Yes

						// Are we at the end of the line?
						if (c == 13 || c == 10)
							goto skip_to_next_line;

						// Mark the start
						cb->value.data_s8 = properties->data_s8 + lnI;


					//////////
					// Find out how long the value is
					//////
						for (lnLength = 0; lnI + lnLength < properties->length; lnLength++)
						{
							// Continue until we reach CR or LF
							if ((c = properties->data_s8[lnI + lnLength]) == 13 || c == 10)
								break;	// We're done
						}

						// Did we go too far?
						if (lnI >= properties->length)
							return(lnProperties);		// Yes

						// Store the length
						cb->value.length = lnLength;

						// Move past it
						lnI += lnLength;


					//////////
					// Dispatch the property
					//////
						++lnProperties;
						if (!cb->propAndValue_func(cb))
							return(lnProperties);		// They've completed processing


skip_to_next_line:
				//////////
				// Skip forward to the CR/LF characters
				//////
					while ((c = properties->data_s8[lnI]) != 13 && c != 10 && lnI < properties->length)
						++lnI;

					// Did we go too far?
					if (lnI >= properties->length)
						return(lnProperties);		// Yes

					// Skip past all CR/LF characters
					while ((c = properties->data_s8[lnI]) == 13 || c == 10)
						++lnI;

			}

			// All properties are exhausted
			// Indicate how many properties we've processed
			return(lnProperties);
		}

		// If we get here, invalid params
		return(-1);
	}
#endif
