//////////
//
// /libsf/source/vjr/source/object_accessors.cpp
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
// Version 0.57
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Jul.12.2014
//////
// Change log:
//     Jul.12.2014 - Initial creation
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
//
// To jump immediately to a section, search for one of these here or in object_accessors.h:
//		OBJECT Properties
//		FORM Properties
//		SUBFORM Properties
//
//////








//////////
//
// Called one time at startup to initialize the settings for a particular value
// since MSVC doesn't allow population of a variable type into a union, except
// for the first named member, at compile time.
//
//////
	void iObjProp_init_fixup(void)
	{
		// Fixups to populate SBasePropMap values that cannot be populated into the union at compile time (without resorting to an obtuse integer-based hex encoding)
		gsProps_master[_INDEX_INCREMENT - 1]._f64	= 1.0;		// Default to 1.0 for incrementing
		gsProps_master[_INDEX_ROUND_TO  - 1]._f64	= 0.01;		// Default to 2 decimal places
	}




//////////
//
// Called to set the f64 variable to the indicated input
//
// Note:  For nested sets, such as something already calling setterObject_set(), which then calls here,
//        we want it to then go through the normal setterObject() function.
//
//////
	bool iObjProp_set(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable* varNewValue, bool tlNestedSet)
	{
		bool			llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Validate against the object class if available, and if not then the base class if available, and if not then just copy
				     if (objProp->_setterObject && !tlNestedSet && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else if (objProp->_setterObject_set && !tlNestedSet && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
				else if (baseProp->_setterBase)																	llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else																							llResult = iVariable_copy(thisCode, var, varNewValue);

				// Indicate our status
				return(llResult);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the bitmap to the indicated bitmap
//
//////
	bool iObjProp_set_bitmap_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, SBitmap* bmp)
	{
		bool			llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		varNewValue;
		SVariable*		var;
		SObject*		objChild;
		RECT			lrc;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_NULL, NULL, true);
				varNewValue->bmp = bmp;

				// Perform the set
				     if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
				else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else																			llResult = iVariable_set_bitmap(thisCode, var, bmp);

				// If they just set the picture on an image or checkbox, then we need to propagate through to the down and over
				if ((obj->objType == _OBJ_TYPE_IMAGE || obj->objType == _OBJ_TYPE_CHECKBOX) && tnIndex == _INDEX_PICTUREBMP)
				{
					// Set the two
					iObjProp_set_bitmap_direct(thisCode, obj, _INDEX_PICTUREBMP_DOWN, bmp);
					iObjProp_set_bitmap_direct(thisCode, obj, _INDEX_PICTUREBMP_OVER, bmp);

					// Colorize
					SetRect(&lrc, 0, 0, bmp->bi.biWidth, bmp->bi.biHeight);
					bmp = iObjProp_get_bitmap(thisCode, obj, _INDEX_PICTUREBMP_OVER);		iBmp_colorize(bmp, &lrc, colorMouseOver, false, 0.25f + ((obj->objType == _OBJ_TYPE_CHECKBOX) ? 0.25f : 0.0f));
					bmp = iObjProp_get_bitmap(thisCode, obj, _INDEX_PICTUREBMP_DOWN);		iBmp_colorize(bmp, &lrc, colorMouseDown, false, 0.25f + ((obj->objType == _OBJ_TYPE_CHECKBOX) ? 0.25f : 0.0f));

				} else if ((obj->objType == _OBJ_TYPE_FORM || obj->objType == _OBJ_TYPE_SUBFORM) && tnIndex == _INDEX_ICON) {
					// Icons propagate through to the child's _icon member as their picturebmp
					objChild = obj->firstChild;
					while (objChild)
					{
						if (objChild->objType == _OBJ_TYPE_IMAGE && propIsName_byText(objChild, cgcName_icon))
						{
							// Sets the three by setting the one (see how it handles _INDEX_PICTUREBMP above)
							iObjProp_set_bitmap_direct(thisCode, objChild, _INDEX_PICTUREBMP, bmp);

							// All done
							break;
						}

						// Move to the next sibling
						objChild = objChild->ll.nextObj;

					}
				}

				// Delete our temporary variable
				iVariable_delete(thisCode, varNewValue, true);

				// Indicate our status
				return(llResult);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the character variable to the indicated input
//
//////
	bool iObjProp_set_character_direct (SThisCode* thisCode, SObject* obj, s32 tnIndex, cs8* tcText, u32 tnTextLength)
	{
		return(iObjProp_set_character_direct(thisCode, obj, tnIndex, (u8*)tcText, tnTextLength));
	}

	bool iObjProp_set_character_direct (SThisCode* thisCode, SObject* obj, s32 tnIndex, s8* tcText, u32 tnTextLength)
	{
		return(iObjProp_set_character_direct(thisCode, obj, tnIndex, (u8*)tcText, tnTextLength));
	}

	bool iObjProp_set_character_direct (SThisCode* thisCode, SObject* obj, s32 tnIndex, cu8* tcText, u32 tnTextLength)
	{
		return(iObjProp_set_character_direct(thisCode, obj, tnIndex, (u8*)tcText, tnTextLength));
	}

	bool iObjProp_set_character_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, u8* tcText, u32 tnTextLength)
	{
		bool			llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		varNewValue;
		SVariable*		var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, tcText, tnTextLength, false);

				// Perform the set
				     if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
				else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else																			llResult = iVariable_copy(thisCode, var, varNewValue);

				// Delete our temporary variable
				iVariable_delete(thisCode, varNewValue, true);

				// Indicate our status
				return(llResult);
			}
		}
		// If we get here, failure
		return(false);
	}

	bool iObjProp_set_character_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, SDatum* datum)
	{
		bool			llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		varNewValue;
		SVariable*		var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_createAndPopulate_byDatum(thisCode, _VAR_TYPE_CHARACTER, datum, true);

				// Perform the set
				     if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
				else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
				else																			llResult = iVariable_copy(thisCode, var, varNewValue);

//////////
// Include some extra debugging information to aid in tracking down those little peskies
//////
#ifdef _EXTRA_DEBUGGING_DATA
	switch (tnIndex)
	{
		case _INDEX_CLASS:
			iDatum_duplicate(&obj->dbgClass, varNewValue);
			break;

		case _INDEX_NAME:
			iDatum_duplicate(&obj->dbgName, varNewValue);
			break;
	}
#endif

				// Delete our temporary variable
				iVariable_delete(thisCode, varNewValue, true);

				// Indicate our status
				return(llResult);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the s32 variable directly by value
//
//////
	bool iObjProp_set_logical_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, bool tlValue)
	{
		return(iObjProp_set_logical_fromLogicalConstants(thisCode, obj, tnIndex, ((tlValue) ? _LOGICAL_TRUE : _LOGICAL_FALSE)));
	}

	bool iObjProp_set_logical_fromLogicalConstants(SThisCode* thisCode, SObject* obj, s32 tnIndex, s32 tnValue)
	{
		bool			llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*		varNewValue;
		SVariable*		var;


		// Make sure the environment is sane
		if (obj)
		{
			switch (tnValue)
			{
				case _LOGICAL_TRUE:
				case _LOGICAL_FALSE:
				case _LOGICALX_OTHER:
				case _LOGICALX_PARTIAL:
				case _LOGICALX_EXTRA:
				case _LOGICALX_YET_ANOTHER:
				case _LOGICALX_ZATS_ALL_FOLKS:
					break;

				default:
					tnValue = _LOGICAL_FALSE;
					break;
			}

			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_LOGICAL, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_logical(thisCode, varNewValue, tnValue);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the s32 variable directly by value
//
//////
	bool iObjProp_set_s32_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, s32 tnValue)
	{
		bool				llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*			varNewValue;
		SVariable*			var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_S32, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_s32(thisCode, varNewValue, tnValue);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the u32 variable directly by value
//
//////
	bool iObjProp_set_u32_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, u32 tnValue)
	{
		bool				llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*			varNewValue;
		SVariable*			var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_U32, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_u32(thisCode, varNewValue, tnValue);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the f32 value directly by value
//
//////
	bool iObjProp_set_f32_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, f32 tfValue)
	{
		bool				llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*			varNewValue;
		SVariable*			var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_F32, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_f32(thisCode, varNewValue, tfValue);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the f64 value directly by value
//
//////
	bool iObjProp_set_f64_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, f64 tfValue)
	{
		bool				llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*			varNewValue;
		SVariable*			var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_F64, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_f64(thisCode, varNewValue, tfValue);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the SBgra variable directly by value
//
//////
	bool iObjProp_set_sbgra_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex, SBgra color)
	{
		bool				llResult;
		SBasePropMap*	baseProp;
		SObjPropMap*	objProp;
		SVariable*			varNewValue;
		SVariable*			var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex, &baseProp, &objProp);
			if (var)
			{
				// Create a temporary variable
				varNewValue = iVariable_create(thisCode, _VAR_TYPE_U32, NULL, true);
				if (varNewValue)
				{
					// Populate the variable the indicated value
					iVariable_set_u32(thisCode, varNewValue, color.color);

					// Perform the set
						 if (objProp->_setterObject && tnIndex < (s32)_INDEX_SET_FIRST_ITEM)		llResult = objProp->setterObject(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else if (objProp->_setterObject_set && tnIndex >= (s32)_INDEX_SET_FIRST_ITEM)	llResult = objProp->setterObject_set(thisCode, var, NULL, varNewValue, false);
					else if (baseProp->_setterBase)													llResult = baseProp->setterBase	(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);
					else																			llResult = iVariable_copy(thisCode, var, varNewValue);

					// Delete our temporary variable
					iVariable_delete(thisCode, varNewValue, true);

					// Indicate our status
					return(llResult);
				}
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to copy the indicated variable
//
//////
	bool iObjProp_copy_byIndex(SThisCode* thisCode, SObject* objDst, s32 tnIndexDst, SObject* objSrc, s32 tnIndexSrc)
	{
		SVariable* varDst;
		SVariable* varSrc;


		// Make sure the environment is sane
		if (objDst && objSrc)
		{
			// Grab the variable associated with this object's property
			varDst = iObjProp_get_variable_byIndex(thisCode, objDst, tnIndexDst);
			varSrc = iObjProp_get_variable_byIndex(thisCode, objSrc, tnIndexDst);
			if (varDst && varSrc)
				return(iVariable_copy(thisCode, varDst, varSrc));
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Copy all of the properties
//
//////
	bool iObjProp_copyAll(SThisCode* thisCode, SObject* objDst, SObject* objSrc, bool tlCopyDynamicProperties)
	{
		s32		lnI;
		bool	llResult;


		// Make sure the environment is sane
		llResult = false;
		if (objDst && objSrc && objSrc->props && objSrc->propsCount > 0)
		{
			//////////
			// Delete any properties which already exist
			//////
				if (objDst->props && objDst->propsCount > 0)
				{
					// Delete the variables one-by-one
					for (lnI = 0; lnI < objDst->propsCount; lnI++)
					{
						// Not all properties may be populated, but they should be
						if (objDst->props[lnI])
						{
							// Delete the variable
							iVariable_delete(thisCode, objDst->props[lnI], true);
							objDst->props[lnI] = NULL;
						}
					}

					// Delete the props allocation
					free(objDst->props);
					objDst->props = NULL;
				}


			//////////
			// Allocate space for the props
			//////
				objDst->props = (SVariable**)malloc(objSrc->propsCount * sizeof(SObject*));
				if (!objDst->props)
				{
					// Should never happen
					debug_break;
					iError_track();

				} else {

					//////////
					// Iterate through each prop one by one
					//////
						objDst->propsCount = objSrc->propsCount;
						for (lnI = 0; lnI < objSrc->propsCount; lnI++)
						{
							// Copy the property if populated
							if (objSrc->props[lnI])
								objDst->props[lnI] = iVariable_copy(thisCode, objSrc->props[lnI], false);
						}


					//////////
					// Copy dynamic properties if need be
					//////
						if (tlCopyDynamicProperties)		llResult = iObjProp_copyDynamic(thisCode, objDst, objSrc);
						else								llResult = true;
				}

		}

		// Indicate success or failure
		return(llResult);
	}




//////////
//
// Copy the dynamic runtime properties
//
//////
	bool iObjProp_copyDynamic(SThisCode* thisCode, SObject* objDst, SObject* objSrc)
	{
		bool		llResult;
		SVariable*	var;
		SVariable*	varNew;
		SVariable*	varNext;


		// Make sure our environment is sane
		llResult = false;
		if (objDst && objSrc)
		{

			//////////
			// Delete any existing properties
			//////
				if (objDst->firstProperty)
				{
// Untested code, breakpoint and examine
debug_break;
					// Delete each property in the chain
					for (var = objDst->firstProperty; var; var = varNext)
					{
						// Grab the next property
						varNext = var->ll.nextVar;

						// Delete it
						iVariable_delete(thisCode, var, true);
					}

					// Indicate they're gone
					objDst->firstProperty = NULL;
				}


			//////////
			// Early out
			//////
				if (!objSrc->firstProperty)
					return(true);		// Nothing to copy


			//////////
			// Copy all of the existing properties
			//////
// Untested code, breakpoint and examine
debug_break;
				for (var = objSrc->firstProperty; var; var = var->ll.nextVar)
				{
					// Copy it
					varNew = iVariable_copy(thisCode, var, false);

					// Append it
					iLl_appendExistingNodeAtEnd((SLL**)&objSrc->firstProperty, (SLL*)varNew);
				}

		}

		// Indicate our status
		return(llResult);
	}




//////////
//
// Called to set the value using an on/off component
//
//////
	bool iObjProp_setOnOff(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate the component is an ON or OFF
		//////
			llResult = false;
			if (compNew && (compNew->iCode == _ICODE_ON || compNew->iCode == _ICODE_OFF))
			{
				// Set the value
				iVariable_set_logical(thisCode, varSet, ((compNew->iCode == _ICODE_ON) ? _LOGICAL_TRUE : _LOGICAL_FALSE));

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the value using the valid date texts
//
//////
	bool iObjProp_setDate(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		u32		lnDateType;
		bool	llResult;


		// Make sure we have a component
		if (compNew)
		{
			// Default to success
			llResult = true;
			switch (compNew->iCode)
			{
				case _ICODE_AMERICAN:		lnDateType = _SET_DATE_AMERICAN;		break;
				case _ICODE_ANSI:			lnDateType = _SET_DATE_ANSI;			break;
				case _ICODE_BRITISH:		lnDateType = _SET_DATE_BRITISH;			break;
				case _ICODE_DMY:			lnDateType = _SET_DATE_DMY;				break;
				case _ICODE_FRENCH:			lnDateType = _SET_DATE_FRENCH;			break;
				case _ICODE_GERMAN:			lnDateType = _SET_DATE_GERMAN;			break;
				case _ICODE_ITALIAN:		lnDateType = _SET_DATE_ITALIAN;			break;
				case _ICODE_JAPAN:			lnDateType = _SET_DATE_JAPAN;			break;
				case _ICODE_LONG:			lnDateType = _SET_DATE_LONG;			break;
				case _ICODE_MDY:			lnDateType = _SET_DATE_MDY;				break;
				case _ICODE_SHORT:			lnDateType = _SET_DATE_SHORT;			break;
				case _ICODE_TAIWAN:			lnDateType = _SET_DATE_TAIWAN;			break;
				case _ICODE_USA:			lnDateType = _SET_DATE_USA;				break;
				case _ICODE_YMD:			lnDateType = _SET_DATE_YMD;				break;

				default:
					// Failure ... syntax error
					llResult = false;
			}


			//////////
			// Should the value be set?
			//////
				if (llResult)
					iVariable_set_u32(thisCode, varSet, lnDateType);


		} else {
			// Invalid component
			llResult = false;
		}

		// Indicate our result
		return(llResult);
	}




//////////
//
// Called to set the integer using the valid settings for decimals (0..18)
//
//////
	bool iObjProp_setDecimals(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s32		lnDecimals;
		bool	llResult;
		bool	error;
		u32		errorNum;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isTypeNumeric(varNew))
			{
				//////////
				// Grab our value
				//////
					lnDecimals = iiVariable_getAs_s32(thisCode, varNew, false, &error, &errorNum);
					if (!error && lnDecimals >= (s32)_MIN_SET_DECIMALS && lnDecimals <= (s32)_MAX_SET_DECIMALS)
					{
						// Set the value
						iVariable_set(thisCode, varSet, varNew);

						// Indicate success
						llResult = true;
					}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the device output to some location
//
//////
	bool iObjProp_setDevice(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s32			lnLength;
		bool		llResult, llManufactured, llIsValid;
		SComp*		compScreen;
		SComp*		compPrinter;
		SComp*		compPrompt;
		SComp*		compFile;
		SComp*		compFilename;
		SComp*		compAdditive;
		SVariable*	varLookup;
		SVariable*	varFilename;
		s8			buffer[_MAX_PATH];


		//////////
		// Locate any additional components
		//////
			compScreen		= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_SCREEN,		NULL);
			compPrinter		= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_PRINTER,	NULL);
			compPrompt		= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_PROMPT,		NULL);
			compFile		= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_FILE,		NULL);
			compAdditive	= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_ADDITIVE,	NULL);


		//////////
		// Are they specifying a number?
		//////
			llResult = false;
			if (compNew)
			{
				// What are they choosing?
				if (compNew == compScreen)
				{
					// SET DEVICE TO SCREEN
					llResult = true;
					iVariable_set_s32(thisCode, varSet, _SET_DEVICE_SCREEN);

				} else if (compNew == compPrinter) {
					// SET DEVICE TO PRINTER
					llResult = true;
					if (compPrompt)		iVariable_set_s32(thisCode, varSet, _SET_DEVICE_PRINTER_PROMPT);
					else				iVariable_set_s32(thisCode, varSet, _SET_DEVICE_PRINTER_NO_PROMPT);

				} else if (compNew == compFile) {
					// SET DEVICE TO FILE
					// Did they specify a filename?
					if ((compFilename = compFile->ll.nextComp))
					{
						// Yes, try to open the file
						memset(buffer, 0, sizeof(buffer));
						switch (compFilename->iCode)
						{
							case _ICODE_SINGLE_QUOTED_TEXT:
							case _ICODE_DOUBLE_QUOTED_TEXT:
								// It's quoted text, meaning a filename
								llIsValid = true;
								memcpy(buffer, compFilename->line->sourceCode->data_cs8 + compFilename->start, compFilename->length);
								break;

							default:
								// It's something other than quoted text
								// See if it's a variable
								llIsValid	= false;
								varLookup	= iEngine_get_variableName_fromComponent(thisCode, compFilename, &llManufactured, false);
								if (!varLookup)
								{
									// It's not a known variable, so it must be just something they want to use as a filename
									llIsValid	= true;
									lnLength	= iComps_getContiguousLength(thisCode, compFilename, NULL, 0, NULL);
									memcpy(buffer, compFilename->line->sourceCode->data_cs8 + compFilename->start, lnLength);

								} else {
									// Based on the variable type, try to open it
									if (varLookup->varType == _VAR_TYPE_CHARACTER)
									{
										llIsValid = true;
										memcpy(buffer, varLookup->value.data_cs8, varLookup->value.length);
									}
								}

								// Clean house
								if (varLookup && llManufactured)
									iVariable_delete(thisCode, varLookup, true);
						}

						// If we're still valid, try to open the filename
						if (llIsValid)
						{
							// Open the file as additive, or a new blank file
							if (compAdditive)		varSet->meta = (void*)iDisk_openExclusive(buffer, _O_BINARY | _O_WRONLY | _O_APPEND,	true);
							else					varSet->meta = (void*)iDisk_openExclusive(buffer, _O_BINARY | _O_WRONLY | _O_CREAT,		true);

							// Did the file open okay?
							if (varSet->_meta != -1)
							{
								// Indicate success
								llResult = true;
								iVariable_set_s32(thisCode, varSet, _SET_DEVICE_FILE);

								// Create a variable for population into _INDEX_SET_DEVICE2's character memory variable
								varFilename = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, buffer, (s32)strlen(buffer), false);
								if (varFilename)
								{
									// Copy it over
									iObjProp_set(thisCode, _settings, _INDEX_SET_DEVICE2, varFilename, true);

									// Clean house
									iVariable_delete(thisCode, varFilename, true);

								} else {
									// Failure on indicating our filename
									// Note:  At this point it is still set to the correct file, we just won't be able to report on it
									llResult = false;
								}
							}
						}
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate
		//////
			return(llResult);
	}




//////////
//
// Called to set the integer using the valid integer variable
//
//////
	bool iObjProp_setInteger(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isTypeNumeric(varNew))
			{
				// Set the value
				iVariable_set(thisCode, varSet, varNew);

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the integer to either 12 or 24
//
//////
	bool iObjProp_setIneger_12_24(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s32		lnValue;
		bool	llResult;
		bool	error;
		u32		errorNum;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isTypeNumeric(varNew))
			{
				// Gab the value
				lnValue = iiVariable_getAs_s32(thisCode, varNew, false, &error, &errorNum);
				if (!error && (lnValue == 12 || lnValue == 24))
				{
					// Set the value
					iVariable_set(thisCode, varSet, varNew);

					// Indicate success
					llResult = true;
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the integer to the closest 64-bit range from the value indicated, using a minimum of 128
//
//////
	bool iObjProp_setInteger_bits(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s32		lnValue;
		bool	llResult;
		bool	error;
		u32		errorNum;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isTypeNumeric(varNew))
			{
				// Gab the value
				lnValue = iiVariable_getAs_s32(thisCode, varNew, false, &error, &errorNum);
				if (!error)
				{
					// Potentially adjust the value
					lnValue = max(128, ((lnValue / 64) + ((lnValue % 64 != 0) ? 1 : 0)) * 64);
					iVariable_setNumeric_toNumericType(thisCode, varNew, NULL, NULL, &lnValue, NULL, NULL, NULL);

					// Set the value
					iVariable_set(thisCode, varSet, varNew);

					// Indicate success
					llResult = true;
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the u16 value from the indicated input
//
//////
	bool iObjProp_set_u16(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s64		lnValue;
		bool	llResult;
		bool	error;
		u32		errorNum;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isTypeNumeric(varNew))
			{
				//////////
				// Grab our value
				//////
					lnValue = iiVariable_getAs_s64(thisCode, varNew, false, &error, &errorNum);
					if (!error && lnValue >= 0 && lnValue <= (s64)_u16_max)
					{
						// Set the value
						iVariable_set(thisCode, varSet, varNew);

						// Indicate success
						llResult = true;
					}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the value using the valid date texts
//
//////
	bool iObjProp_setLanguage(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
// TODO:  This will need to be implemented once we get resources moved out to loadable DLLs.  We'll look for a vjrres_en.dll, for example
		return(false);
	}




//////////
//
// Called to set the logical using the variable converted to logical
//
//////
	bool iObjProp_setLogical(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate it's numeric
		//////
			llResult = false;
			if (iVariable_isValid(varNew) && iVariable_isFundamentalTypeLogical(varNew))
			{
				// Set the value
				iVariable_set(thisCode, varSet, varNew);

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to indicate how logical variables should be displayed.
// Defaults to TF.
//
///////
	bool iObjProp_setLogicalX(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		u32		lnLogicalType;
		bool	llResult;


		// Make sure we have a component
		if (compNew)
		{
			// Default to success
			llResult = true;
			switch (compNew->iCode)
			{
				// .T. and .F.
				case _ICODE_DEFAULT:
				case _ICODE_TRUE:
				case _ICODE_FALSE:
				case _ICODE_TF:
					lnLogicalType = _LOGICAL_TF;
					break;

				// .U. and .D.
				case _ICODE_UP:
				case _ICODE_DOWN:
				case _ICODE_UD:
					lnLogicalType = _LOGICAL_UD;
					break;

				// .Y. and .N.
				case _ICODE_YES:
				case _ICODE_NO:
				case _ICODE_YN:
					lnLogicalType = _LOGICAL_YN;
					break;

				default:
					// Failure ... syntax error
					llResult = false;
			}


			//////////
			// Should the value be set?
			//////
				if (llResult)
					iVariable_set_u32(thisCode, varSet, lnLogicalType);


		} else {
			// Invalid component
			llResult = false;
		}

		// Indicate our result
		return(llResult);
	}




//////////
//
// Called to set reprocess using the valid reprocess options
//
// Note:  Reprocess is logical, or numeric. When numeric if negative it is attempts, if positive it is seconds
//
//////
	bool iObjProp_setReprocess(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		s32		lnValue;
		bool	llResult;
		SComp*	compSystem;
		SComp*	compSeconds;
		bool	error;
		u32		errorNum;


		//////////
		// Locate any additional components
		//////
			compSystem	= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_SYSTEM, NULL);
			compSeconds	= iComps_findNextBy_iCode(thisCode, compNew, _ICODE_SECONDS, NULL);


		//////////
		// Are they specifying a number?
		//////
			llResult = false;
			if (iVariable_isValid(varNew))
			{
				// It's a value, which means it must not
				if (iVariable_isTypeNumeric(varNew))
				{
					// Grab the value
					lnValue = iiVariable_getAs_s32(thisCode, varNew, false, &error, &errorNum);

					// Must be positive, and there must have been no error in conversion
					if (lnValue >= 0 && !error)
					{
						// Indicate success
						llResult = true;


						//////////
						// Is it seconds or attempts?
						//////
							if (!compSeconds)
								*varNew->value.data_s32 *= -1;		// It is ATTEMPTS, make negative


						//////////
						// Perform the set
						//////
							if (compSystem)
							{
								// Setting the system reprocess
								iObjProp_set(thisCode, _settings, _INDEX_SET_REPROCESS_SYSTEM, varNew, true);

							} else {
								// Setting the normal reprocess
								iObjProp_set(thisCode, _settings, _INDEX_SET_REPROCESS, varNew, true);
							}

					}
				}

			} else if (compNew && compNew->iCode == _ICODE_AUTOMATIC) {
				// They're indicating that it should be automatic processing
				// Indicate success
				llResult = true;


				//////////
				// Perform the set
				//////
					if (compSystem)
					{
						// Setting the system reprocess to true (automatic)
						iObjProp_set(thisCode, _settings, _INDEX_SET_REPROCESS_SYSTEM, cvarTrue, true);

					} else {
						// Setting the normal reprocess to true (automatic)
						iObjProp_set(thisCode, _settings, _INDEX_SET_REPROCESS, cvarTrue, true);
					}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate
		//////
			return(llResult);
	}




//////////
//
// Called to set the time using the valid time texts
//
//////
	bool iObjProp_setTime(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate the component is a SYSTEM or LOCAL
		//////
			llResult = false;
			if (compNew && (compNew->iCode == _ICODE_SYSTEM || compNew->iCode == _ICODE_LOCAL))
			{
				// Set the value
				iVariable_set_s32(thisCode, varSet, ((compNew->iCode == _ICODE_SYSTEM) ? _TIME_SYSTEM : _TIME_LOCAL));

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the user-defined parameter passing protocol to reference or value
//
//////
	bool iObjProp_setUdfParams(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate the component is a SYSTEM or LOCAL
		//////
			llResult = false;
			if (compNew && (compNew->iCode == _ICODE_REFERENCE || compNew->iCode == _ICODE_VALUE))
			{
				// Set the value
				iVariable_set_s32(thisCode, varSet, ((compNew->iCode == _ICODE_REFERENCE) ? _UDFPARMS_REFERENCE : _UDFPARMS_VALUE));

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);

	}




//////////
//
// Called to set the expression to the input character expression
//
//////
	bool iObjProp_setCharacter(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate the variable is character
		//////
			llResult = false;
			if (iVariable_isTypeCharacter(varNew) && varNew->value.length >= 1)
			{
				llResult = true;
				iVariable_copy(thisCode, varSet, varNew);
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to set the expression to the left-most character of the input character expression
//
//////
	bool iObjProp_setCharacter1(SThisCode* thisCode, SVariable* varSet, SComp* compNew, SVariable* varNew, bool tlDeleteVarNewAfterSet)
	{
		bool llResult;


		//////////
		// Validate the variable is character
		//////
			llResult = false;
			if (iVariable_isTypeCharacter(varNew) && varNew->value.length >= 1)
			{
				// Set the value
				iDatum_duplicate(&varSet->value, varNew->value.data_cs8, 1);

				// Indicate success
				llResult = true;
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarNewAfterSet)
				iVariable_delete(thisCode, varNew, true);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}




//////////
//
// Called to obtain the date type of the indicated variable
//
//////
	SVariable* iObjProp_getDate(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeNumeric(varSet))
			{
				// Get the setting as an s32
				lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
				if (!error)
				{
					// Okay... which one are we?
					switch (lnValue)
					{
						default:
						case _SET_DATE_AMERICAN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_american, sizeof(cgc_american) - 1, false);
							break;
						case _SET_DATE_ANSI:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_ansi, sizeof(cgc_ansi) - 1, false);
							break;
						case _SET_DATE_BRITISH:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_british, sizeof(cgc_british) - 1, false);
							break;
						case _SET_DATE_DMY:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_dmy, sizeof(cgc_dmy) - 1, false);
							break;
						case _SET_DATE_FRENCH:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_french, sizeof(cgc_french) - 1, false);
							break;
						case _SET_DATE_GERMAN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_german, sizeof(cgc_german) - 1, false);
							break;
						case _SET_DATE_ITALIAN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_italian, sizeof(cgc_italian) - 1, false);
							break;
						case _SET_DATE_JAPAN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_japan, sizeof(cgc_japan) - 1, false);
							break;
						case _SET_DATE_LONG:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_long, sizeof(cgc_long) - 1, false);
							break;
						case _SET_DATE_MDY:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_mdy, sizeof(cgc_mdy) - 1, false);
							break;
						case _SET_DATE_SHORT:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_short, sizeof(cgc_short) - 1, false);
							break;
						case _SET_DATE_TAIWAN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_taiwan, sizeof(cgc_taiwan) - 1, false);
							break;
						case _SET_DATE_USA:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_usa, sizeof(cgc_usa) - 1, false);
							break;
						case _SET_DATE_YMD:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_ymd, sizeof(cgc_ymd) - 1, false);
							break;
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the current device setting
//
//////
	SVariable* iObjProp_getDevice(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet))
			{
				if (iVariable_isTypeNumeric(varSet))
				{
					// Get the setting as an s32
					lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
					if (!error)
					{
						// Positive = seconds, negative = attempts
						switch (lnValue)
						{
							case _SET_DEVICE_PRINTER_NO_PROMPT:
							case _SET_DEVICE_PRINTER_PROMPT:
								result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_printer, sizeof(cgc_printer) - 1, false);
								break;

							case _SET_DEVICE_FILE:
								result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_file, sizeof(cgc_file) - 1, false);
								break;

							default:
								result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_screen, sizeof(cgc_screen) - 1, false);
								break;
						}
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the integer of the indicated variable
//
//////
	SVariable* iObjProp_getInteger(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		SVariable* result;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeNumeric(varSet))
				result = iVariable_copy(thisCode, varSet, false);


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the language setting of the indicated variable
//
//////
	SVariable* iObjProp_getLanguage(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
// TODO:  This will need to be implemented once we get resources moved out to loadable DLLs.  We'll look for a vjrres_en.dll, for example
		return(NULL);
	}




//////////
//
// Called to obtain the logical setting of the indicated variable
//
//////
	SVariable* iObjProp_getLogical(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		SVariable* result;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeLogical(varSet))
				result = iVariable_copy(thisCode, varSet, false);


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the logicalx setting of the indicated variable
//
//////
	SVariable* iObjProp_getLogicalX(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeNumeric(varSet))
			{
				// Get the setting
				lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
				if (!error)
				{
					// Okay... which one are we?
					switch (lnValue)
					{
						default:
						case _LOGICAL_TF:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_default, sizeof(cgc_default) - 1, false);
							break;
						case _LOGICAL_YN:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_yn, sizeof(cgc_yn) - 1, false);
							break;
						case _LOGICAL_UD:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_ud, sizeof(cgc_ud) - 1, false);
							break;
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the on/off status of the indicated variable
//
//////
	SVariable* iObjProp_getOnOff(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		bool		llOn;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeLogical(varSet))
			{
				// Get the ON/OFF setting as a logical
				llOn = iiVariable_getAs_bool(thisCode, varSet, false, &error, &errorNum);
				if (!error)
				{
					// Okay... are we ON or OFF?
					if (llOn)
					{
						// ON
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_on, sizeof(cgc_on) - 1, false);

					} else {
						// OFF
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_on, sizeof(cgc_on) - 1, false);
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the reprocess setting of the indicated variable
//
//////
	SVariable* iObjProp_getReprocess(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		bool		llAutomatic;
		SVariable*	result;
		s8			buffer[32];
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet))
			{
				if (iVariable_isTypeLogical(varSet))
				{
					// If .T. then AUTOMATIC, if .F. then it's an error because only logical true is supported here
					llAutomatic = iiVariable_getAs_bool(thisCode, varSet, false, &error, &errorNum);
					if (!error)
					{
						// If true, it's valid
						if (llAutomatic)
						{
							// It's set to automatic
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_automatic, sizeof(cgc_automatic) - 1, false);

						} else {
							// This should never happen
							iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, false, NULL, false);
							debug_nop;
						}
					}

				} else {
					// It's set to either a number of attempts or seconds
					// Get the setting as an s32
					lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
					if (!error)
					{
						// Positive = seconds, negative = attempts
						if (lnValue >= 0)
						{
							// Seconds
							sprintf(buffer, "%d %s\0", lnValue, cgc_seconds);

						} else {
							// Attempts
							sprintf(buffer, "%d\n", lnValue * (-1));
						}

						// Create the variable
						result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, buffer, (u32)strlen(buffer), false);
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Called to obtain the time setting of the indicated variable
//
//////
	SVariable* iObjProp_getTime(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeNumeric(varSet))
			{
				// Get the setting
				lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
				if (!error)
				{
					// Okay... are we LOCAL or SYSTEM?
					switch (lnValue)
					{
						default:
						case _TIME_LOCAL:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_local, sizeof(cgc_local) - 1, false);
							break;

						case _TIME_SYSTEM:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_system, sizeof(cgc_system) - 1, false);
							break;
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);
	}




//////////
//
// Returns reference or value
//
//////
	SVariable* iObjProp_getUdfParams(SThisCode* thisCode, SVariable* varSet, SComp* compIdentifier, bool tlDeleteVarSetBeforeReturning)
	{
		s32			lnValue;
		SVariable*	result;
		bool		error;
		u32			errorNum;


		//////////
		// Make sure our environment is sane
		//////
			result = NULL;
			if (iVariable_isValid(varSet) && iVariable_isTypeNumeric(varSet))
			{
				// Get the setting
				lnValue = iiVariable_getAs_s32(thisCode, varSet, false, &error, &errorNum);
				if (!error)
				{
					// Okay... are we REFERENCE or VALUE?
					switch (lnValue)
					{
						default:
						case _UDFPARMS_VALUE:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_value, sizeof(cgc_value) - 1, false);
							break;

						case _UDFPARMS_REFERENCE:
							result = iVariable_createAndPopulate_byText(thisCode, _VAR_TYPE_CHARACTER, cgc_reference, sizeof(cgc_reference) - 1, false);
							break;
					}
				}
			}


		//////////
		// Optionally clean house
		//////
			if (tlDeleteVarSetBeforeReturning)
				iVariable_delete(thisCode, varSet, true);


		//////////
		// Indicate our result
		//////
			return(result);

	}




//////////
//
// Called to get the f64 variable from the indicated object
//
//////
	SVariable* iObjProp_get(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		// Make sure the environment is sane
		if (obj)
			return(iObjProp_get_variable_byIndex(thisCode, obj, tnIndex));

		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to get the type of the variable for the indicated property
//
//////
	s32 iObjProp_getVarAndType(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable** varDst)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			//////////
			// Make sure we have a target
			//////
				if (!varDst)
					varDst = &var;


			//////////
			// Grab the variable
			//////
				*varDst = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);


			//////////
			// Indicate the type
			//////
				if (*varDst)
					return((*varDst)->varType);
		}

		// If we get here, failure
		return(null0);
	}




//////////
//
// Get the associated variable based upon the object type and property index.
//
// Note:  For performance, the value returned here is a pointer to the direct
//        variable, not a copy.
//
//////
	SVariable* iObjProp_get_variable_byIndex(SThisCode* thisCode, SObject* obj, s32 tnIndex, SBasePropMap** baseProp, SObjPropMap** objProp)
	{
		s32				lnI;
		SBaseClassMap*	baseClassMap;
		SObjPropMap*	thisObjProp;


		// Make sure the environment is sane
		if (obj)
		{
			// Locate the base class
// TODO:  We could add a speedup here by storing the baseClassMap location in the object itself at the time of creation
			baseClassMap = iiObj_getBaseclass_byType(thisCode, obj->objType);
			if (baseClassMap)
			{
				// Locate the property within the object's properties
				thisObjProp = baseClassMap->objProps;
// TODO:  We could add a speedup by sorting at startup each baseclassList->objProps, and then use a binary search
				for (lnI = 0; lnI < baseClassMap->objPropsCount && lnI < thisObjProp[lnI].index; lnI++)
				{
					// Is this it?
					if (thisObjProp[lnI].index == tnIndex)
					{
						// Store the raw property entries (if requested)
						if (baseProp)		*baseProp	= &gsProps_master[tnIndex - 1];
						if (objProp)		*objProp	= &thisObjProp[lnI];

						// Return the variable associated with this position
						return(obj->props[lnI]);
					}
				}
				// If we get here, not found
			}
		}

// This should never happen.
// If it does it's a design-time error.  Search the call stack to determine which _INDEX_* variable was referenced.
// That variable needs to be added to the gsProps_* related to this object (such as gsProps_empty for objType = _OBJ_TYPE_EMPTY).
// If a new class has been added, it might be missing from gsKnownBaseclasses as per the iiObj_getBaseclass_byType() function.
debug_break;
		// Invalid
		return(NULL);
	}




//////////
//
// Get the associated variable based optionally upon (1) the object type and property index,
// or (2) an add-on user property.
//
//		tlSearchBaseProps	-- Search obj->props[] array for standard properties for the class
//		tlSearchClassProps	-- Search obj->firstProperty link list for custom added properties with ADDPROPERTY()
//
//////
	SVariable* iObjProp_get_variable_byComp(SThisCode* thisCode, SObject* obj, SComp* comp, bool tlSearchBaseProps, bool tlSearchClassProps, u32* tnIndex)
	{
		// Make sure our environment is sane
		if (comp && comp->line && comp->line->sourceCode && comp->line->sourceCode->data_s8 && comp->start + comp->length <= comp->line->sourceCode->length)
		{
			// We're good
			return(iObjProp_get_variable_byName(thisCode, obj, comp->line->sourceCode->data_u8 + comp->start, comp->length, tlSearchBaseProps, tlSearchClassProps, tnIndex));

		} else {
			// Something's invalid
			return(NULL);
		}
	}

	SVariable* iObjProp_get_variable_byName(SThisCode* thisCode, SObject* obj, u8* tcName, u32 tnNameLength, bool tlSearchBaseProps, bool tlSearchClassProps, u32* tnIndex)
	{
		s32					lnI, lnIndex;
		SBaseClassMap*		baseClassMap;
		SObjPropMap*		thisObjProp;


		// Make sure the environment is sane
		if (obj)
		{
			// Search base class properties
			if (tlSearchBaseProps)
			{
				// Locate the base class
// TODO:  We could add a speedup here by storing the baseClassMap location in the object itself at the time of creation
				baseClassMap = iiObj_getBaseclass_byType(thisCode, obj->objType);
				if (baseClassMap)
				{
					// Locate the property within the object's properties
					thisObjProp = baseClassMap->objProps;
					for (lnI = 0; lnI < baseClassMap->objPropsCount && lnI < thisObjProp[lnI].index; lnI++)
					{
						// Grab this property's index
						lnIndex = thisObjProp[lnI].index;

						// Search the name associated with that property
						if (iTestExactlyEqual(tcName, tnNameLength, gsProps_master[lnIndex - 1].propName_u8, gsProps_master[lnIndex - 1].propNameLength))
							return(obj->props[lnI]);	// Return the variable associated with this position
					}
					// If we get here, not found
				}

				// If we get here, there's an internal system error
				iError_signal(thisCode, _ERROR_INTERNAL_ERROR, NULL, true, NULL, true);
				return(NULL);
			}

			// Locate the user property
			if (tlSearchClassProps)
			{
// TODO:  Write code to search for dynamically allocated properties (allocated at runtime)
			}
		}

		// Invalid
		return(NULL);
	}




//////////
//
// Called to get the bitmap from the indicated object
//
//////
	SBitmap* iObjProp_get_bitmap(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_BITMAP)
				return(var->bmp);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to get the character from the indicated object
//
//////
	SVariable* iObjProp_get_character(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_CHARACTER)
				return(var);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to get the f32 variable from the indicated object
//
//////
	SVariable* iObjProp_get_f32(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_F32)
				return(var);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to get the f32 from the indicated object
//
//////
	f64 iObjProp_get_f32_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		bool		error;
		f32			lfResult;
		u32			errorNum;
		SVariable*	var;


		// Make sure the environment is sane
		lfResult = _f32_min;
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_F32)
			{
				// Try to get the value
				return(iiVariable_getAs_f32(thisCode, var, false, &error, &errorNum));

				// If we got it...
				if (!error)
					return(lfResult);	// ...return the value

				// Reset the value to the minimum value
				lfResult = _f32_min;
			}
		}
		// If we get here, failure
		return(lfResult);
	}




//////////
//
// Called to get the f64 from the indicated object
//
//////
	f64 iObjProp_get_f64_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		bool		error;
		f64			lfResult;
		u32			errorNum;
		SVariable*	var;


		// Make sure the environment is sane
		lfResult = _f64_min;
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var)
			{
				// Try to get the value
				return(iiVariable_getAs_f64(thisCode, var, false, &error, &errorNum));

				// If we got it...
				if (!error)
					return(lfResult);	// ...return the value

				// Reset the value to the minimum value
				lfResult = _f64_min;
			}
		}
		// If we get here, failure
		return(lfResult);
	}




//////////
//
// Called to get the logical from the indicated object
//
//////
	SVariable* iObjProp_get_logical(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_LOGICAL)
				return(var);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to obtain the property's direct value
//
//////
	s32 iObjProp_get_logical_fromLogicalConstants(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		bool		error;
		s32			lnResult;
		u32			errorNum;
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var)
			{
				// Try to get the value
				lnResult = iiVariable_getAs_s32(thisCode, var, false, &error, &errorNum);

				// If we got it...
				if (!error)
					return(lnResult);	// ...return the value
			}
		}
		// If we get here, failure
		return(_LOGICAL_FALSE);
	}




//////////
//
// Called to get the object from the indicated object
//
//////
	SVariable* iObjProp_get_object(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_OBJECT)
				return(var);
		}
		// If we get here, failure
		return(NULL);
	}




//////////
//
// Called to get the s8 from the indicated object directly
//
//////
	s8 iObjProp_get_s8_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		bool		error;
		s32			lnResult;
		u32			errorNum;
		SVariable*	var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var)
			{
				// Try to get the value
				lnResult = iiVariable_getAs_s8(thisCode, var, false, &error, &errorNum);

				// If we got it...
				if (!error)
					return(lnResult);	// ...return the value
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to get the s32 from the indicated object directly
//
//////
	s32 iObjProp_get_s32_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		bool		error;
		s32			lnResult;
		u32			errorNum;
		SVariable*	var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var)
			{
				// Try to get the value
				lnResult = iiVariable_getAs_s32(thisCode, var, false, &error, &errorNum);

				// If we got it...
				if (!error)
					return(lnResult);	// ...return the value
			}
		}
		// If we get here, failure
		return(-1);
	}




//////////
//
// Called to obtain the s32 value as an SBgra color
//
//////
	SBgra iObjProp_get_sbgra_direct(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		s64			_color64;
		union {
			u32		_color;
			SBgra	color;
		};
		bool		error;
		u32			errorNum;
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var)
			{
				// Try to get the value
				_color64 = iiVariable_getAs_s64(thisCode, var, false, &error, &errorNum);
				_color	= (u32)_color64;

				// If we got it...
				if (!error)
					return(color);		// ...return the value

			}
		}
		// If we get here, failure
		_color = -1;
		return(color);
	}




//////////
//
// Called to translate the xyz keyword used in the SET xzy TO abc expression
// into its proper _INDEX_SET_* value.
//
//////
	s32 iObjProp_settingsTranslate(SThisCode* thisCode, s32 tniCodeKeyword)
	{
		SBasePropMap* baseProps;


		//////////
		// Iterate though looking for the matching keyword
		//////
			for (baseProps = (SBasePropMap*)&gsProps_master[0]; baseProps->index != 0; baseProps++)
			{
				// Is this our iCode?
				if (baseProps->associated_iCode == tniCodeKeyword)
					return(baseProps->index);		// We found our match
			}


		//////////
		// If we get here, not found
		//////
			return(-1);
	}




//////////
//
// Called to delete the variable associated with the index
//
//////
	bool iObjProp_delete_variable_byIndex(SThisCode* thisCode, SObject* obj, s32 tnIndex)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_BITMAP)
			{
				iVariable_delete(thisCode, var, false);
				return(true);
			}
		}
		// If we get here, failure
		return(false);
	}




//////////
//
// Called to compare the indicated character variable with the indicated text
//
//////
	s32 iObjProp_compare_character(SThisCode* thisCode, SObject* obj, s32 tnIndex, s8* tcText, u32 tnTextLength)
	{
		SVariable* var;


		// Make sure the environment is sane
		if (obj)
		{
			// Grab the variable associated with this object's property
			var = iObjProp_get_variable_byIndex(thisCode, obj, tnIndex);
			if (var && var->varType == _VAR_TYPE_CHARACTER)
				return(iDatum_compare(&var->value, tcText, tnTextLength));	// Do the compare normally
		}
		// If we get here, does not match
		return(-2);
	}




//////////
//
// Called to set the caption on items which have captions.  The caption is not merely on
// the parent, but subforms also contain a default child object called _caption which
// has its own properties, and these are used for rendering.
//
//////
	bool iObjProp_setter_captionOnChild(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable* var, SVariable* varNewValue, SBasePropMap* baseProp, SObjPropMap* objProp)
	{
		SObject*	objChild;
		SVariable*	varChild;


		// Make sure our environment is sane
		if (obj && var && varNewValue)
		{
			// Set the caption
			iVariable_copy(thisCode, var, varNewValue);

			// For the items with captions, we set the caption on the parent as well as the child
			objChild = obj->firstChild;
			while (objChild)
			{
				// Is this the one
				if (propIsName_byText(objChild, cgcName_caption))
				{
					// Set the caption here
					varChild = iObjProp_get_variable_byIndex(thisCode, objChild, _INDEX_CAPTION);
					if (varChild)
						return(iVariable_copy(thisCode, varChild, varNewValue));

					// If we get here, we could not update it
					break;
				}

				// Move to next sibling
				objChild = objChild->ll.nextObj;
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the icon on items which have captions.  The icon is not merely on the
// parent, but forms and subforms also contain a default child object called _icon which
// has its own properties, and these are used for rendering.
//
//////
	bool iObjProp_setter_iconOnChild(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable* var, SVariable* varNewValue, SBasePropMap* baseProp, SObjPropMap* objProp)
	{
		SObject*	objChild;
		SVariable*	varChild;


		// Make sure our environment is sane
		if (obj && var && varNewValue)
		{
			// Set the caption
			iVariable_copy(thisCode, var, varNewValue);

			// For the items with captions, we set the caption on the parent as well as the child
			objChild = obj->firstChild;
			while (objChild)
			{
				// Is this the one
				if (propIsName_byText(objChild, cgcName_icon))
				{
					// Set the caption here
					varChild = iObjProp_get_variable_byIndex(thisCode, objChild, _INDEX_ICON);
					if (varChild)
						return(iVariable_copy(thisCode, varChild, varNewValue));

					// If we get here, we could not update it
					break;
				}

				// Move to next sibling
				objChild = objChild->ll.nextObj;
			}
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to mirror the color setting into the parent object into the nested child object
//
//////
	bool iObjProp_setter_editboxMirror(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable* var, SVariable* varNewValue, SBasePropMap* baseProp, SObjPropMap* objProp)
	{
		// Make sure our environment is sane
		if (obj && obj->objType == _OBJ_TYPE_EDITBOX && var && varNewValue)
		{
			// Copy it to the SEM
			switch (tnIndex)
			{
				case _INDEX_READONLY:
					obj->p.sem->isReadOnly				= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_OVERWRITE:
					obj->p.sem->isOverwrite				= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_SHOW_LINE_NUMBERS:
					obj->p.sem->showLineNumbers			= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_SHOW_CURSOR_LINE:
					obj->p.sem->showCursorLine			= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_SHOW_END_LINE:
					obj->p.sem->showEndLine				= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_IS_HEAVY_PROCESSING:
					obj->p.sem->isHeavyProcessing		= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_IS_SOURCE_CODE:
					obj->p.sem->isSourceCode				= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_ALLOW_MOVE_BEYOND_END_OF_LINE:
					obj->p.sem->allowMoveBeyondEndOfLine	= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_EDITBOX_COLUMN:
					obj->p.sem->columnEdit					= *varNewValue->value.data_s32;
					break;

				case _INDEX_EDITBOX_LEFT_COLUMN:
					obj->p.sem->columnLeft				= *varNewValue->value.data_s32;
					break;

				case _INDEX_EDITBOX_TAB_WIDTH:
					obj->p.sem->tabWidth					= *varNewValue->value.data_s32;
					break;

				case _INDEX_EDITBOX_TABS_ENFORCED:
					obj->p.sem->areTabsEnforced				= (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
					break;

				case _INDEX_FONTBOLD:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isBold = obj->p.font->isBold;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTCHARSET:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->charset = obj->p.font->charset;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTCONDENSE:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isCondensed = obj->p.font->isCondensed;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTEXTEND:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isExtended = obj->p.font->isExtended;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTITALIC:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isItalic = obj->p.font->isItalic;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTNAME:
					if (obj->p.sem->font)
					{
						iDatum_duplicate(&obj->p.sem->font->name, &obj->p.font->name);
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTOUTLINE:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isOutline = obj->p.font->isOutline;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTSHADOW:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isShadow = obj->p.font->isShadow;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTSIZE:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->_size = obj->p.font->_size;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTSTRIKETHRU:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isStrikethrough = obj->p.font->isStrikethrough;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				case _INDEX_FONTUNDERLINE:
					if (obj->p.sem->font)
					{
						obj->p.sem->font->isUnderline = obj->p.font->isUnderline;
						iiFont_refresh(obj->p.sem->font);
					}
					break;

				default:
					// Set the property to whatever is indicated, even though there is no mirror value in the SEM
					iVariable_copy(thisCode, var, varNewValue);
			}

			// Success
			return(true);
		}

		// If we get here, failure
		return(false);
	}




//////////
//
// Called to set the font object members associated with the object's font property settings.
//
//////
	bool iObjProp_setter_fontProperty(SThisCode* thisCode, SObject* obj, s32 tnIndex, SVariable* var, SVariable* varNewValue, SBasePropMap* baseProp, SObjPropMap* objProp)
	{
		bool llResult;


		//////////
		// Perform the actual set on the property
		//////
			llResult = iVariable_copy(thisCode, var, varNewValue);
			if (llResult)
			{
				//////////
				// Using the property, update and reset the font object
				/////
					switch (tnIndex)
					{
						case _INDEX_FONTBOLD:
							obj->p.font->isBold = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTCHARSET:
							obj->p.font->charset = *varNewValue->value.data_s32;
							break;

						case _INDEX_FONTCONDENSE:
							obj->p.font->isCondensed = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTEXTEND:
							obj->p.font->isExtended = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTITALIC:
							obj->p.font->isItalic = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTNAME:
							iDatum_duplicate(&obj->p.sem->font->name, &obj->p.font->name);
							break;

						case _INDEX_FONTOUTLINE:
							obj->p.font->isOutline = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTSHADOW:
							obj->p.font->isShadow = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTSIZE:
							obj->p.font->_size = *varNewValue->value.data_s32;
							break;

						case _INDEX_FONTSTRIKETHRU:
							obj->p.font->isStrikethrough = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						case _INDEX_FONTUNDERLINE:
							obj->p.font->isUnderline = (varNewValue->value.data_s8[0] != _LOGICAL_FALSE);
							break;

						default:
							// This should never happen.  It's the result of a developer error at compile-time
							debug_break;
							break;
					}


				//////////
				// Refresh the font for this item
				//////
					iiFont_refresh(obj->p.font);


				//////////
				// Signal that this object needs redrawn
				//////
					iObj_setDirtyRender_ascent(thisCode, obj, true);
			}


		//////////
		// For editboxes, we need to mirror the font settings through to the SEM
		//////
			if (obj->objType == _OBJ_TYPE_EDITBOX)
				iObjProp_setter_editboxMirror(thisCode, obj, tnIndex, var, varNewValue, baseProp, objProp);


		//////////
		// Indicate our status
		//////
			return(llResult);
	}
