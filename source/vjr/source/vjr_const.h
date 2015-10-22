//////////
//
// /libsf/source/vjr/source/vjr_const.h
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
//     Feb.12.2014
//////
// Change log:
//     Feb.12.2014 - Initial creation
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
//




struct SVariable;
struct SObject;
struct SEM;


#if defined(_MSC_VER)
	#include "\libsf\utils\common\cpp\common_types.h"
#elif defined(__GNUC__)
	#include "/libsf/utils/common/cpp/common_types.h"
#elif defined(__solaris__)
	#include "/libsf/utils/common/cpp/common_types.h"
#else
	#error Unknown target for compilation (must be Windows, Linux, or Solaris (OpenIndiana))
#endif

// Used for passing complex parameters as references, such as SObjectpp&, or SEMpp&
typedef SObject**	SObjectpp;
typedef SEM**		SEMpp;


//////////
// Union helper
//////
	#define _union(x, y, z) union { x z; y _ ## z; };


//////////
// For the lower 256 values of flag-mapped comp->iCat codes
//////
	#define iCat(x)										(x & 0xff)


//////////
// Macros
//////
	// abc = newAlloc(SAbc, gsAbcRoot);
	#define newAlloc(str, var)							(str*)iLl_appendNewNodeAtEnd((SLL**)&var, sizeof(str))
	#define between(value, lo, hi)						(value >= lo && value <= hi)


//////////
// Macro helpers
//////
	// Note:  A variable can still have its original type and be NULL, so you must also test var->value members:
	#define iVariable_isNull(var)						(var->varType == _VAR_TYPE_NULL || !var->value.data || (var->varType != _VAR_TYPE_CHARACTER && var->value.length == 0))
	#define iVariable_getType(var)						var->varType
	#define iVariable_isFundamentalTypeLogical(var)		(var->varType == _VAR_TYPE_LOGICAL || (iVariable_areTypesCompatible(thisCode, var, varDefault_logical)))
	#define iVariable_isNumeric64Bit(var)				(var->varType == _VAR_TYPE_S64 || var->varType == _VAR_TYPE_U64 || var->varType == _VAR_TYPE_CURRENCY || var->varType == _VAR_TYPE_DATETIMEX)
	#define iVariable_isTypeBig(var)					(var->varType == _VAR_TYPE_BI || var->varType == _VAR_TYPE_BFP)
	#define iVariable_isTypeBigFloatingPoint(var)		(var->varType == _VAR_TYPE_BFP)
	#define iVariable_isTypeBigInteger(var)				(var->varType == _VAR_TYPE_BI)
	#define iVariable_isTypeCharacter(var)				(var->varType == _VAR_TYPE_CHARACTER)
	#define iVariable_isTypeCurrency(var)				(var->varType == _VAR_TYPE_CURRENCY)
	#define iVariable_isTypeDate(var)					(var->varType == _VAR_TYPE_DATE)
	#define iVariable_isTypeDatetime(var)				(var->varType == _VAR_TYPE_DATETIME)
	#define iVariable_isTypeDatetimeX(var)				(var->varType == _VAR_TYPE_DATETIMEX)
	#define iVariable_isTypeDouble(var)					(var->varType == _VAR_TYPE_F64)
	#define iVariable_isTypeFloat(var)					(var->varType == _VAR_TYPE_F32)
	#define iVariable_isTypeFloatingPoint(var)			(var->varType == _VAR_TYPE_F32 || var->varType == _VAR_TYPE_F64)
	#define iVariable_isTypeInteger(var)				(var->varType >= _VAR_TYPE_NUMERIC_INTEGER_START && var->varType <= _VAR_TYPE_NUMERIC_INTEGER_END)
	#define iVariable_isTypeLogical(var)				(var->varType == _VAR_TYPE_LOGICAL)
	#define iVariable_isTypeNumeric(var)				(var->varType >= _VAR_TYPE_NUMERIC_START && var->varType <= _VAR_TYPE_NUMERIC_END)
	#define iVariable_isTypeObject(var)					(var->varType == _VAR_TYPE_OBJECT)
	#define iVariable_isTypethisCode(var)				(var->varType == _VAR_TYPE_THISCODE)
	#define iVariable_isValid(var)						(var && var->varType >= _VAR_TYPE_START && var->varType <= _VAR_TYPE_END && var->value.data && (var->varType == _VAR_TYPE_CHARACTER || var->value.length > 0))
	#define iVariable_isValidType(var)					(var && var->varType >= _VAR_TYPE_START && var->varType <= _VAR_TYPE_END)
	#define iVariable_isEmpty(var)						(!var->value.data || var->value.length <= 0)

	#define validateVariable(var, error)				if (!iVariable_isValid(var)) \
														{ \
															iError_reportByNumber(thisCode, error, iVariable_getRelatedComp(thisCode, var), false); \
															return; \
														}

	#define validateNumeric(var, error)					if (!iVariable_isTypeNumeric(var)) \
														{ \
															iError_reportByNumber(thisCode, error, iVariable_getRelatedComp(thisCode, var), false); \
															return; \
														}

	#define validateCharacter(var, error)				if (!iVariable_isTypeCharacter(var)) \
														{ \
															iError_reportByNumber(thisCode, error, iVariable_getRelatedComp(thisCode, var), false); \
															return; \
														}

	#define validateFloatingPoint(var, error)			if (!iVariable_isTypeFloatingPoint(var)) \
														{ \
															iError_reportByNumber(thisCode, error, iVariable_getRelatedComp(thisCode, var), false); \
															return; \
														}

	#define getAs_s32(local, var)						local = iiVariable_getAs_s32(thisCode, var, false, &error, &errorNum); \
														if (error) \
														{ \
															iError_reportByNumber(thisCode, errorNum, iVariable_getRelatedComp(thisCode, var), false); \
															return; \
														}

	#define propHasCaption(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_HASCAPTION)	!= _LOGICAL_FALSE)
	#define propIsEnabled(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_ENABLED)		!= _LOGICAL_FALSE)
	#define propIsFalse(obj, index)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, index)				== _LOGICAL_FALSE)
	#define propIsName_byText(obj, t)					(iObjProp_compare_character		(thisCode, obj, _INDEX_NAME,		(s8*)t,		sizeof(t) - 1) == 0)
	#define propIsName_byDatum(obj, d)					(iObjProp_compare_character		(thisCode, obj, _INDEX_NAME,		d->data_s8, d->length) == 0)
	#define propIsReadonly(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_READONLY)		!= _LOGICAL_FALSE)
	#define propIsTrue(obj, index)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, index)				!= _LOGICAL_FALSE)
	#define propIsVisible(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_VISIBLE)		!= _LOGICAL_FALSE)

	#define propX(obj)									((obj) ? obj->rc.left : 0)
	#define propY(obj)									((obj) ? obj->rc.top : 0)
	#define propWidth(obj)								((obj) ? obj->rc.right - obj->rc.left: 0)
	#define propHeight(obj)								((obj) ? obj->rc.bottom - obj->rc.top : 0)

	#define propAlignment(obj)							iObjProp_get_s32_direct			(thisCode, obj, _INDEX_ALIGNMENT)
	#define propBackColor(obj)							iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_BACKCOLOR)
	#define propBackStyle(obj)							iObjProp_get_s32_direct			(thisCode, obj, _INDEX_BACKSTYLE)
	#define propBaseclass(obj)							iObjProp_get_character			(thisCode, obj, _INDEX_BASECLASS);
	#define propBorderColor(obj)						iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_BORDERCOLOR)
	#define propBorderStyle(obj)						iObjProp_get_s32_direct			(thisCode, obj, _INDEX_BORDERSTYLE)
	#define propClass(obj)								iObjProp_get_character			(thisCode, obj, _INDEX_CLASS);
	#define propClassLibrary(obj)						iObjProp_get_character			(thisCode, obj, _INDEX_CLASSLIBRARY);
	#define propForeColor(obj)							iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_FORECOLOR)
	#define propMargin(obj)								iObjProp_get_s32_direct			(thisCode, obj, _INDEX_MARGIN)
	#define propName(obj)								iObjProp_get_character			(thisCode, obj, _INDEX_NAME);
	#define propNeRgba(obj)								iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_NECOLOR)
	#define propNwRgba(obj)								iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_NWCOLOR)
	#define propSeRgba(obj)								iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_SECOLOR)
	#define propRiderTab(obj)							iObjProp_get_character			(thisCode, obj, _INDEX_RIDERTAB)
	#define propRiderTabCloseable(obj)					(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_RIDERTABCLOSEABLE)	!= _LOGICAL_FALSE)
	#define propSpecialEffect(obj)						iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SPECIALEFFECT)
	#define propSwRgba(obj)								iObjProp_get_sbgra_direct		(thisCode, obj, _INDEX_SWCOLOR)
	#define propTitleBar(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_TITLEBAR)	!= _LOGICAL_FALSE)

	#define propSetValueMaximum(obj, value)				iObjProp_set_f64_direct			(thisCode, obj, _INDEX_VALUE_MAXIMUM,		value)
	#define propSetValueMinimum(obj, value)				iObjProp_set_f64_direct			(thisCode, obj, _INDEX_VALUE_MINIMUM,		value)
	#define propSetValue_f64(obj, value)				iObjProp_set_f64_direct			(thisCode, obj, _INDEX_VALUE,				value)
	#define propSetValue_s32(obj, value)				iObjProp_set_s32_direct			(thisCode, obj, _INDEX_VALUE,				value)
	#define propSetValueRoundTo(obj, value)				iObjProp_set_f64_direct			(thisCode, obj, _INDEX_ROUND_TO,			value)

	#define propSetBackColor(obj, color)				iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_BACKCOLOR,			color)
	#define propSetBorderColor(obj, color)				iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_BORDERCOLOR,			color)
	#define propSetDisabledBackColor(obj, color)		iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_DISABLEDBACKCOLOR,	color)
	#define propSetDisabledForeColor(obj, color)		iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_DISABLEDFORECOLOR,	color)
	#define propSetForeColor(obj, color)				iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_FORECOLOR,			color)
	#define propSetSelectedBackColor(obj, color)		iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_SELECTEDBACKCOLOR,	color);
	#define propSetSelectedForeColor(obj, color)		iObjProp_set_sbgra_direct		(thisCode, obj, _INDEX_SELECTEDFORECOLOR,	color);

	#define propSetAlignment(obj, value)				iObjProp_set_s32_direct			(thisCode, obj, _INDEX_ALIGNMENT,			value)
	#define propSetAnchor(obj, value)					iObjProp_set_s32_direct			(thisCode, obj, _INDEX_ANCHOR,				value)
	#define propSetBackStyle(obj, value)				iObjProp_set_s32_direct			(thisCode, obj, _INDEX_BACKSTYLE,			value)
	#define propSetBorderStyle(obj, value)				iObjProp_set_s32_direct			(thisCode, obj, _INDEX_BORDERSTYLE,			value)
	#define propSetCaption(obj, value)					iObjProp_set_character_direct	(thisCode, obj, _INDEX_CAPTION,				(u8*)value,		sizeof(value) - 1)
	#define propSetCount(obj, value)					iObjProp_set_s32_direct			(thisCode, obj, _INDEX_COUNT,				value)
	#define propSetEnabled(obj, value)					iObjProp_set_logical_fromLogicalConstants(thisCode, obj, _INDEX_ENABLED, value);
	#define propSetIcon(obj, bmp)						iObjProp_set_bitmap_direct		(thisCode, obj, _INDEX_ICON,				bmp)
	#define propSetMargin(obj, value)					iObjProp_set_s32_direct			(thisCode, obj, _INDEX_MARGIN,				value)
	#define propSetMultiSelect(obj, value)				iObjProp_set_logical_fromLogicalConstants(thisCode, obj, _INDEX_MULTISELECT, value)
	#define propSetName(obj, value, valueLength)		iObjProp_set_character_direct	(thisCode, obj, _INDEX_NAME,				(u8*)value,		valueLength)
	#define propSetPictureBmp(obj, bmp)					iObjProp_set_bitmap_direct		(thisCode, obj, _INDEX_PICTUREBMP,			bmp)
	#define propSetPictureBmpDown(obj, bmp)				iObjProp_set_bitmap_direct		(thisCode, obj, _INDEX_PICTUREBMP_DOWN,		bmp)
	#define propSetRiderTab(obj, value, valueLength)	iObjProp_set_character_direct	(thisCode, obj, _INDEX_RIDERTAB,			(u8*)value,		valueLength)
	#define propSetStyle(obj, value)					iObjProp_set_s32_direct			(thisCode, obj, _INDEX_STYLE,				value)
	#define propSetTitlebar(obj, value)					iObjProp_set_logical_fromLogicalConstants(thisCode, obj, _INDEX_TITLEBAR,	value)
	#define propSetVisible(obj, value)					iObjProp_set_logical_fromLogicalConstants(thisCode, obj, _INDEX_VISIBLE,	value)
	#define propSetVisible_fromBool(obj, value)			iObjProp_set_logical_direct(thisCode, obj, _INDEX_VISIBLE, value)
	#define propSetPictureBmpOver(obj, bmp)				iObjProp_set_bitmap_direct		(thisCode, obj, _INDEX_PICTUREBMP_OVER,		bmp)


//////////
// _settings macros
//////
	#define propGet_settings_AutoConvert(obj)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_AUTO_CONVERT)			!= _LOGICAL_FALSE)
	#define propGet_settings_AutoValidate(obj)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_AUTO_VALIDATE)			!= _LOGICAL_FALSE)
	#define propGet_settings_Century(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_CENTURY)					!= _LOGICAL_FALSE)
	#define propGet_settings_Currency(obj)							iObjProp_get_character			(thisCode, obj, _INDEX_SET_CURRENCY)
	#define propGet_settings_Date(obj)								iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_DATE)
	#define propGet_settings_Decimals(obj)							iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_DECIMALS)
	#define propGet_settings_Exclusive(obj)							(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_EXCLUSIVE)				!= _LOGICAL_FALSE)
	#define propGet_settings_FocusHighlightBorderPixels(obj)		iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_FOCUS_HIGHLIGHT_BORDER_PIXELS)
	#define propGet_settings_Hours(obj)								iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_HOURS)
	#define propGet_settings_Hours12(obj)							(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_HOURS)							== 12)
	#define propGet_settings_Hours24(obj)							(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_HOURS)							== 24)
	#define propGet_settings_FocusHighlightPixels(obj)				iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_FOCUS_HIGHLIGHT_PIXELS)
	#define propGet_settings_InitializeDefaultValue(obj)			iObjProp_get_variable_byIndex	(thisCode, obj, _INDEX_SET_INITIALIZE_DEFAULT_VALUE)
	#define propGet_settings_LoadReceivesParams(obj)				(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_LOAD_RECEIVES_PARAMS)	!= _LOGICAL_FALSE)
	#define propGet_settings_LockScreen(obj)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_LOCK_SCREEN)			!= _LOGICAL_FALSE)
	#define propGet_settings_Logical(obj)							iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_LOGICAL)
	#define propGet_settings_Mark(obj)								iObjProp_get_character			(thisCode, obj, _INDEX_SET_MARK)
	#define propGet_settings_ncset(obj, index)						(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, index)							!= _LOGICAL_FALSE)
	#define propSet_settings_ncset_fromBool(obj, index, value)		iObjProp_set_logical_direct		(thisCode, obj, index, value)
	#define propGet_settings_ncset_alphaIsOpaque(obj)				propGet_settings_ncset(obj, _INDEX_SET_NCSET_ALPHA_IS_OPAQUE)
	#define propGet_settings_ncset_ceilingFloor(obj)				propGet_settings_ncset(obj, _INDEX_SET_NCSET_CEILING_FLOOR)
	#define propGet_settings_ncset_datetimeMilliseconds(obj)		propGet_settings_ncset(obj, _INDEX_SET_NCSET_DATETIME_MILLISECONDS)
	#define propGet_settings_ncset_optimizeTableWrites(obj)			propGet_settings_ncset(obj, _INDEX_SET_NCSET_OPTIMIZE_TABLE_WRITES)
	#define propGet_settings_ncset_optimizeVariables(obj)			propGet_settings_ncset(obj, _INDEX_SET_NCSET_OPTIMIZE_VARIABLES)
	#define propGet_settings_ncset_signSign2(obj)					propGet_settings_ncset(obj, _INDEX_SET_NCSET_SIGN_SIGN2)
	#define propGet_settings_ncset_directNativeMembers(obj)			propGet_settings_ncset(obj, _INDEX_SET_NCSET_DIRECT_NATIVE_MEMBERS)
	#define propGet_settings_Point(obj)								iObjProp_get_character			(thisCode, obj, _INDEX_SET_POINT)
	#define propGet_settings_PrecisionBFP(obj)						iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_PRECISIONBFP)
	#define propGet_settings_PrecisionBI(obj)						iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_PRECISIONBI)
	#define propGet_settings_Reprocess(obj)							iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_REPROCESS)	// negative attempts, positive seconds
	#define propGet_settings_ReprocessAttempts(obj)					iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_REPROCESSATTEMPTS)
	#define propGet_settings_ReprocessInterval(obj)					iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_REPROCESSINTERVAL)
	#define propGet_settings_Separator(obj)							iObjProp_get_character			(thisCode, obj, _INDEX_SET_SEPARATOR)
	#define propGet_settings_Talk(obj)								(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_TALK)					!= _LOGICAL_FALSE)
	#define propGet_settings_Time(obj)								iObjProp_get_s32_direct			(thisCode, obj, _INDEX_SET_TIME)
	#define propGet_settings_TimeLocal(obj)							(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_TIME)							== _TIME_LOCAL)
	#define propGet_settings_TimeSystem(obj)						(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_TIME)							== _TIME_SYSTEM)
	#define propGet_settings_UdfParamsReference(obj)				(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_UDFPARMS)						== _UDFPARMS_REFERENCE)
	#define propGet_settings_UdfParamsValue(obj)					(iObjProp_get_s32_direct		(thisCode, obj, _INDEX_SET_UDFPARMS)						== _UDFPARMS_VALUE)
	#define propGet_settings_VariablesFirst(obj)					(iObjProp_get_logical_fromLogicalConstants(thisCode, obj, _INDEX_SET_VARIABLES_FIRST)		!= _LOGICAL_FALSE)
	#define propGet_settings_VecSeparator(obj)						iObjProp_get_character			(thisCode, obj, _INDEX_SET_VECSEPARATOR)


//////////
// Red,Grn,Blu,Alp color maker
//////
	#define rgba(r,g,b,a)					((a & 0xff) << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff))

	#define rgb(r,g,b)						(0xff       << 24) + \
											((r & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((b & 0xff))

	#define bgra(b,g,r,a)					((a & 0xff) << 24) + \
											((b & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((r & 0xff))

	#define bgr(b,g,r)						(0xff       << 24) + \
											((b & 0xff) << 16) + \
											((g & 0xff) <<  8) + \
											((r & 0xff))

	#define alp(rgbaColor)					((rgbaColor >> 24) & 0xff)
	#define red(rgbaColor)					((rgbaColor >> 16) & 0xff)
	#define grn(rgbaColor)					((rgbaColor >> 8)  & 0xff)
	#define blu(rgbaColor)					( rgbaColor        & 0xff)

	#define _disabledBackColor				rgba(255, 255, 255, 255)
	#define _disabledForeColor				rgba(192, 192, 230, 255)
	#define _whiteColor						rgba(255, 255, 255, 255)
	#define _grayColor						rgba(192, 192, 192, 255)
	#define _blackColor						rgba(0, 0, 0, 255)
	#define _selectedBackColor				rgba(220, 235, 255, 255)
	#define _selectedForeColor				rgba(0, 0, 164, 255)

	#define _nwFocusColor					rgba(255, 245, 235, 255)
	#define _neFocusColor					rgba(245, 225, 215, 255)
	#define _swFocusColor					rgba(245, 225, 215, 255)
	#define _seFocusColor					rgba(235, 215, 215, 255)

	#define _nwColor						rgba(245, 250, 255, 255)
	#define _neColor						rgba(220, 240, 255, 255)
	#define _swColor						rgba(235, 245, 255, 255)
	#define _seColor						rgba(205, 225, 245, 255)


//////////
// min and max
//////
	#ifndef max
		#define max(a,b)					((a >= b) ? a : b)
	#endif
	#ifndef min
		#define min(a,b)					((a <= b) ? a : b)
	#endif


//////////
// Auto-converters
//////
	size_t strlen(s8* p)					{	return(strlen((const char*)p));		}
	size_t strlen(u8* p)					{	return(strlen((const char*)p));		}


// Definitions missing in MinGW
#if !defined(WM_MOUSEHWHEEL)
	#define WM_MOUSEHWHEEL                  0x020E
#endif
// Missing in MinGW and VC98
#if !defined(CLEARTYPE_NATURAL_QUALITY)
	#define CLEARTYPE_NATURAL_QUALITY       6
#endif
// Missing in x64
#if !defined(GWL_USERDATA)
	#define GWL_USERDATA (-21)
#endif


//////////
// Reference datetimes
//////
	SVariable*			_datetime_Jan_01_2000					= NULL;


//////////
// Min/max constants
//////
	const s8			_s8_min									= (s8)-128;
	const s8			_s8_max									= 127;
	const u8			_u8_max									= 255;
	const s16			_s16_min								= (s16)-32768;
	const s16			_s16_max								= 32767;
	const u16			_u16_max								= 65535;
	const s32			_s32_min								= (2147483647 * -1) - 1;
	const s32			_s32_max								= 2147483647;
	const u32			_u32_max								= 0xffffffff;	// 4294967295;
	const s64			_s64_min								= (9223372036854775807 * -1) - 1;
	const s64			_s64_max								= 9223372036854775807;
	const u64			_u64_max								= 0xffffffffffffffff;	// 18446744073709551615;
	const f32			_f32_min								= 1.175494351e-38f;
	const f32			_f32_max								= 3.402823466e+38f;
	const f64			_f64_min								= 2.22507385850720138e-308;
	const f64			_f64_max								= 1.79769313486231571e+308;


//////////
// Errors
//////
	const u32			_ERROR_OKAY								= 0;
	const u32			_ERROR_OUT_OF_MEMORY					= 1;
	const u32			_ERROR_UNEXPECTED_COMMAND				= 2;
	const u32			_ERROR_CONTEXT_HAS_CHANGED				= 3;
	const u32			_ERROR_FULL_RECOMPILE_REQUIRED			= 4;
	const u32			_ERROR_NOT_A_VARIABLE					= 5;
	const u32			_ERROR_NUMERIC_OVERFLOW					= 6;
	const u32			_ERROR_NOT_NUMERIC						= 7;
	const u32			_ERROR_EMPTY_STRING						= 8;
	const u32			_ERROR_SYNTAX							= 9;
	const u32			_ERROR_UNRECOGNIZED_PARAMETER			= 10;
	const u32			_ERROR_OUT_OF_RANGE						= 11;
	const u32			_ERROR_COMMA_EXPECTED					= 12;
	const u32			_ERROR_TOO_MANY_PARAMETERS				= 13;
	const u32			_ERROR_DATA_TYPE_MISMATCH				= 14;
	const u32			_ERROR_FEATURE_NOT_AVAILABLE			= 15;
	const u32			_ERROR_P1_IS_INCORRECT					= 16;
	const u32			_ERROR_P2_IS_INCORRECT					= 17;
	const u32			_ERROR_P3_IS_INCORRECT					= 18;
	const u32			_ERROR_P4_IS_INCORRECT					= 19;
	const u32			_ERROR_P5_IS_INCORRECT					= 20;
	const u32			_ERROR_P6_IS_INCORRECT					= 21;
	const u32			_ERROR_P7_IS_INCORRECT					= 22;
	const u32			_ERROR_INTERNAL_ERROR					= 23;
	const u32			_ERROR_INVALID_ARGUMENT_TYPE_COUNT		= 24;
	const u32			_ERROR_VARIABLE_NOT_FOUND				= 25;
	const u32			_ERROR_ALIAS_NOT_FOUND					= 26;
	const u32			_ERROR_INVALID_WORK_AREA				= 27;
	const u32			_ERROR_ALIAS_ALREADY_IN_USE				= 28;
	const u32			_ERROR_PARENTHESIS_EXPECTED				= 29;
	const u32			_ERROR_MISSING_PARAMETER				= 30;

	// These relate in a 1:1 ratio with the _DBF_ERROR_* and _CDX_ERROR_* constants of the same name, that are defined internally in dbf.cpp, and cdx.cpp
	const u32			_ERROR_DBF_UNABLE_TO_OPEN_TABLE			= 31;
	const u32			_ERROR_DBF_WORK_AREA_ALREADY_IN_USE		= 32;
	const u32			_ERROR_DBF_ERROR_OPENING_DBC			= 33;
	const u32			_ERROR_DBF_WORK_AREA_NOT_IN_USE			= 34;
	const u32			_ERROR_DBF_ERROR_READING_HEADER1		= 35;
	const u32			_ERROR_DBF_UNKNOWN_TABLE_TYPE			= 36;
	const u32			_ERROR_DBF_MEMORY_ALLOCATION			= 37;
	const u32			_ERROR_DBF_ERROR_READING_HEADER2		= 38;
	const u32			_ERROR_DBF_TABLE_NAME_TOO_LONG			= 39;
	const u32			_ERROR_DBF_MEMORY_ROW					= 40;
	const u32			_ERROR_DBF_MEMORY_ORIGINAL				= 41;
	const u32			_ERROR_DBF_MEMORY_INDEX					= 42;
	const u32			_ERROR_DBF_INVALID_WORK_AREA			= 43;
	const u32			_ERROR_DBF_NO_MORE_WORK_AREAS			= 44;
	const u32			_ERROR_DBF_LOCKING						= 45;
	const u32			_ERROR_DBF_WRITING						= 46;
	const u32			_ERROR_DBF_SEEKING						= 47;
	const u32			_ERROR_DBF_NO_DATA						= 48;
	const u32			_ERROR_DBF_UNKNOWN_MEMO_FORMAT			= 49;

	const u32			_ERROR_CONFLICTING_PARAMETERS			= 80;
	const u32			_ERROR_PARAMETER_IS_INCORRECT			= 81;
	const u32			_ERROR_TABLE_ALREADY_IN_USE				= 82;
	const u32			_ERROR_PARAMETER_TOO_LONG				= 83;
	const u32			_ERROR_UNABLE_TO_OPEN_DBC				= 84;
	const u32			_ERROR_DIVISION_BY_ZERO					= 85;
	const u32			_ERROR_CANNOT_BE_NEGATIVE				= 86;
	const u32			_ERROR_CANNOT_BE_ZERO_OR_NEGATIVE		= 87;
	const u32			_ERROR_UNABLE_TO_AUTOVALIDATE			= 88;
	const u32			_ERROR_DBF_GENERAL_ERROR				= 89;
	const u32			_ERROR_CANNOT_BE_ZERO					= 90;
	const u32			_ERROR_MUST_BE_LOGICAL					= 91;
	const u32			_ERROR_PARAMETER_MUST_BE_8_16_32_64		= 92;
	const u32			_ERROR_TOO_BIG_FOR_TARGET				= 93;
	const u32			_ERROR_NO_INDEX_IS_LOADED				= 94;
	const u32			_ERROR_INVALID_INDEX_TAG				= 95;
	const u32			_ERROR_UNABLE_TO_SAVE					= 96;
	const u32			_ERROR_INVALID_PARAMETERS				= 97;
	const u32			_ERROR_PARAMETER_MUST_BE_1				= 98;
	const u32			_ERROR_INVALID_CORRUPT_NEEDS_REBUILT	= 99;
	const u32			_ERROR_UNABLE_TO_LOCK_FOR_WRITE			= 100;
	const u32			_ERROR_UNABLE_TO_LOCK_FOR_READ			= 101;
	const u32			_ERROR_UNABLE_TO_INITIALIZE				= 102;
	const u32			_ERROR_UNKNOWN_FUNCTION					= 103;
	const u32			_ERROR_DLL_NOT_FOUND					= 104;
	const u32			_ERROR_FUNCTION_NOT_FOUND				= 105;


//////////
// System constants
//////
	const s32			_MENU_BAR_HEIGHT					= 16;						// Each menu is 16 pixels high
	const s32			_SOURCELIGHT_MARGIN					= 8;


//////////
// Tests for IS*() functions
//////
	enum EIsCommonOp
	{
		_isAlpha,
		_isDigit,
		_isLower,
		_isUpper
	};



//////////
// Constants for SCompParams
//////
	const u32			_CP_TYPE_EMPTY						= 1;						// Parameter was not provided, such as fred(,3)
	const u32			_CP_TYPE_COMP						= 2;						// Parameter points to a component on the source code line
	const u32			_CP_TYPE_VAR						= 3;						// Parameter is a variable


//////////
// Time functions
/////
	const u32			_TIME_LOCAL							= 1;						// Local time is adjusted for timezone and daylight saving (if any)
	const u32			_TIME_SYSTEM						= 2;						// Raw time


//////////
// User-defined-function parameter passing protocol
//////
	const u32			_UDFPARMS_VALUE						= 0;						// By value
	const u32			_UDFPARMS_REFERENCE					= 1;						// By reference


//////////
// Constants
//////
	const u32			_MAX_PARAMETER_COUNT				= 26;						// 26 passed parameters
	const u32			_MAX_RETURN_COUNT					= 10;						// 10 return parameters
	const u32			_MAX_DLL_PARAMS						= 26;						// 26 passed parameters into the called DLL


//////////
// Object types
//////
	// Note:  This starting value of 1 is important.  It is used in at least iiObj_getBaseclass_byType() and related functions.
	const u32			_OBJ_TYPE_EMPTY						= 1;						// Empty, used as a placeholder object that is not drawn
	const u32			_OBJ_TYPE_FORM						= 2;						// Form class, the main outer window the OS sees
	const u32			_OBJ_TYPE_SUBFORM					= 3;						// A new class which has its own drawing content and can be moved about using UI features
	const u32			_OBJ_TYPE_CAROUSEL					= 4;						// A carousel is a holder for riders
	const u32			_OBJ_TYPE_RIDER						= 5;						// A rider holds a form or subform and sizes it based on user interaction within its carousel
	const u32			_OBJ_TYPE_LABEL						= 6;						// A label
	const u32			_OBJ_TYPE_TEXTBOX					= 7;						// An input textbox
	const u32			_OBJ_TYPE_BUTTON					= 8;						// A push button
	const u32			_OBJ_TYPE_EDITBOX					= 9;						// An input multi-line editbox
	const u32			_OBJ_TYPE_IMAGE						= 10;						// A graphical image
	const u32			_OBJ_TYPE_CHECKBOX					= 11;						// A checkbox
	const u32			_OBJ_TYPE_OPTION					= 12;						// A combination selection
	const u32			_OBJ_TYPE_RADIO						= 13;						// A radio dial, which can also present as a slider or spinner
	const u32			_OBJ_TYPE_CMDGROUP					= 14;						// A command button group
	const u32			_OBJ_TYPE_OPTGROUP					= 15;						// An option group
	const u32			_OBJ_TYPE_LISTBOX					= 16;						// A listbox
	const u32			_OBJ_TYPE_COMBOBOX					= 17;						// A combobox
	const u32			_OBJ_TYPE_FORMSET					= 18;						// A formset
	const u32			_OBJ_TYPE_TOOLBAR					= 19;						// A toolbar
	const u32			_OBJ_TYPE_SEPARATOR					= 20;						// A separator
	const u32			_OBJ_TYPE_LINE						= 21;						// A line
	const u32			_OBJ_TYPE_SHAPE						= 22;						// A shape
	const u32			_OBJ_TYPE_CONTAINER					= 23;						// A container
	const u32			_OBJ_TYPE_CONTROL					= 24;						// A blocking container
	const u32			_OBJ_TYPE_GRID						= 25;						// A grid
	const u32			_OBJ_TYPE_COLUMN					= 26;						// A grid's column object
	const u32			_OBJ_TYPE_HEADER					= 27;						// A grid's header object
	const u32			_OBJ_TYPE_OLEBOUND					= 28;						// A bound OLE object
	const u32			_OBJ_TYPE_OLECONTAIN				= 29;						// An OLE container control object
	const u32			_OBJ_TYPE_SPINNER					= 30;						// A spinner
	const u32			_OBJ_TYPE_TIMER						= 31;						// A timer
	const u32			_OBJ_TYPE_HYPERLINK					= 32;						// A hyperlink
	const u32			_OBJ_TYPE_COLLECTION				= 33;						// A collection
	const u32			_OBJ_TYPE_PAGE						= 34;						// A page within a pageframe
	const u32			_OBJ_TYPE_PAGEFRAME					= 35;						// A pageframe
	const u32			_OBJ_TYPE_SESSION					= 36;						// A session
	const u32			_OBJ_TYPE_CUSTOM					= 37;						// A custom class
	const u32			_OBJ_TYPE_EXCEPTION					= 38;						// An exception
	const u32			_OBJ_TYPE_SETTINGS					= 39;						// Settings (SET TALK ON, etc.)


//////////
// Constants for date formats
//////
	const u32								_SET_DATE_START	= 1;
	const u32			_SET_DATE_AMERICAN					= 1;			// mm/dd/yy
	const u32			_SET_DATE_ANSI						= 2;			// yy.mm.dd
	const u32			_SET_DATE_BRITISH					= 3;			// dd/mm/yy
	const u32			_SET_DATE_FRENCH					= 4;			// dd/mm/yy
	const u32			_SET_DATE_GERMAN					= 5;			// dd.mm.yy
	const u32			_SET_DATE_ITALIAN					= 6;			// dd-mm-yy
	const u32			_SET_DATE_JAPAN						= 7;			// yy/mm/dd
	const u32			_SET_DATE_TAIWAN					= 8;			// yy/mm/dd
	const u32			_SET_DATE_LONG						= 9;			// Dayofweek, Month dd, yyyy
	const u32			_SET_DATE_SHORT						= 10;			// m/d/yy
	const u32			_SET_DATE_USA						= 11;			// mm-dd-yy
	const u32			_SET_DATE_DMY						= 12;			// dd/mm/yy
	const u32			_SET_DATE_MDY						= 13;			// mm/dd/yy
	const u32			_SET_DATE_YMD						= 14;			// yy/mm/dd
	const u32								_SET_DATE_END	= 14;


//////////
// Constants for device settings
//////
	const u32			_SET_DEVICE_SCREEN					= 0;			// Output is to screen
	const u32			_SET_DEVICE_PRINTER_NO_PROMPT		= 1;			// Output is to printer, do not prompt for printer
	const u32			_SET_DEVICE_PRINTER_PROMPT			= 2;			// Output is to printer, prompt for printer
	const u32			_SET_DEVICE_FILE					= 3;			// Output is to file, use _INDEX_SET_DEVICE2 for filename


//////////
// Event signals
// See:  SEvents
//////
	// Internal signals
	const u32			_EVENT_RESIZE						= 0;

	// External source code / member methods
	const u32			_EVENT_ONLOAD						= 1;
	const u32			_EVENT_ONINIT						= 2;
	const u32			_EVENT_ONCREATED					= 3;
	const u32			_EVENT_ONRESIZE						= 4;
	const u32			_EVENT_ONMOVED						= 5;
	const u32			_EVENT_ONRENDER						= 6;
	const u32			_EVENT_ONPUBLISH					= 7;
	const u32			_EVENT_ONQUERYUNLOAD				= 8;
	const u32			_EVENT_ONDESTROY					= 9;
	const u32			_EVENT_ONUNLOAD						= 10;
	const u32			_EVENT_ONGOTFOCUS					= 11;
	const u32			_EVENT_ONLOSTFOCUS					= 12;
	const u32			_EVENT_ONADDOBJECT					= 13;
	const u32			_EVENT_ONADDPROPERTY				= 14;
	const u32			_EVENT_ONERROR						= 15;
	const u32			_EVENT_ONSCROLLED					= 16;
	const u32			_EVENT_ACTIVATE						= 17;
	const u32			_EVENT_DEACTIVATE					= 18;
	const u32			_EVENT_ONSELECT						= 19;
	const u32			_EVENT_ONDESELECT					= 20;
	const u32			_EVENT_ONINTERACTIVECHANGE			= 21;
	const u32			_EVENT_ONPROGRAMMATICCHANGE			= 22;

	const u32			_EVENT_ONSETACTIVECONTROL			= 23;
	const u32			_EVENT_ONSPIN						= 24;

	const u32			_EVENT_ONMOUSECLICKEX				= 25;
	const u32			_EVENT_ONMOUSEDBLCLICKEX			= 26;
	const u32			_EVENT_ONMOUSEWHEEL					= 27;
	const u32			_EVENT_ONMOUSEMOVE					= 28;
	const u32			_EVENT_ONMOUSEDOWN					= 29;
	const u32			_EVENT_ONMOUSEUP					= 30;
	const u32			_EVENT_ONMOUSEENTER					= 31;
	const u32			_EVENT_ONMOUSELEAVE					= 32;
	const u32			_EVENT_ONMOUSEHOVER					= 33;

	const u32			_EVENT_ONKEYDOWN					= 34;
	const u32			_EVENT_ONKEYUP						= 35;

	// Carousel tab events
	const u32			_EVENT_CAROUSEL_ONTABCLOSE			= 36;
	const u32			_EVENT_CAROUSEL_ONTABCLICK			= 37;
	const u32			_EVENT_CAROUSEL_ONTABMOUSEWHEEL		= 38;
	const u32			_EVENT_CAROUSEL_ONTABMOUSEMOVE		= 39;
	const u32			_EVENT_CAROUSEL_ONTABMOUSEDOWN		= 40;
	const u32			_EVENT_CAROUSEL_ONTABMOUSEUP		= 41;
	const u32			_EVENT_CAROUSEL_ONTABMOUSEENTER		= 42;
	const u32			_EVENT_CAROUSEL_ONTABMOUSELEAVE		= 43;

	const u32			_EVENT_MAX_COUNT					= 43;


//////////
// Carousel internal specific
//////
	const u32			_EVENT_CAROUSEL_AWAY				= 0;			// Elsewhere (not on a header, tab, tab close, or in the tab area)
	const u32			_EVENT_CAROUSEL_TAB					= 1;			// On a physical tab
	const u32			_EVENT_CAROUSEL_TAB_CLOSE			= 2;			// On a physical tab's close button
	const u32			_EVENT_CAROUSEL_TAB_RECTANGLE		= 3;			// Somewhere in the tab rectangle, but not on a tab


//////////
// Constants for .T. and .F. settings using LOGICALX()
//
//////
	const u32			_LOGICAL_TF							= 1;
	const u32			_LOGICAL_UD							= 2;
	const u32			_LOGICAL_YN							= 3;


//////////
// Image styles
//////
	const u32			_IMAGE_STYLE_OPAQUE					= 0;
	const u32			_IMAGE_STYLE_TRANSPARENT			= 1;


//////////
// Option styles
//////
	const u32			_STYLE_PLAIN						= 0;
	const u32			_STYLE_2D							= 1;
	const u32			_STYLE_3D							= 2;


//////////
// Alignment modes
//////
	const u32			_ALIGNMENT_LEFT						= 0;
	const u32			_ALIGNMENT_RIGHT					= 1;
	const u32			_ALIGNMENT_CENTER					= 2;
	const u32			_ALIGNMENT_MIDDLE_LEFT				= 0;
	const u32			_ALIGNMENT_MIDDLE_RIGHT				= 1;
	const u32			_ALIGNMENT_MIDDLE_CENTER			= 2;
	const u32			_ALIGNMENT_TOP_LEFT					= 3;
	const u32			_ALIGNMENT_TOP_RIGHT				= 4;
	const u32			_ALIGNMENT_TOP_CENTER				= 5;
	const u32			_ALIGNMENT_BOTTOM_LEFT				= 7;
	const u32			_ALIGNMENT_BOTTOM_RIGHT				= 8;
	const u32			_ALIGNMENT_BOTTOM_CENTER			= 9;
	// For carousel tab placement (along with left and right above, default is bottom)
	const u32			_ALIGNMENT_TOP						= 10;
	const u32			_ALIGNMENT_BOTTOM					= 11;
	// For rider objects (how they behave inside of carousels)
	const u32			_ALIGNMENT_FIXED					= 100;
	const u32			_ALIGNMENT_SPINS					= 101;


//////////
// Border styles
//////
	const u32			_BORDER_STYLE_NONE					= 0;						// No border, not sizable
	const u32			_BORDER_STYLE_OUTLINE				= 1;						// Outline border, not sizable
	const u32			_BORDER_STYLE_FIXED					= 2;						// Normal border, not sizable
	const u32			_BORDER_STYLE_SIZABLE				= 3;						// Normal border, sizable


//////////
// Back styles
//////
	const u32			_BACK_STYLE_TRANSPARENT				= 0;						// Transparent styles
	const u32			_BACK_STYLE_OPAQUE					= 1;						// Opaque styles


//////////
// Form scale mode
//////
	const u32			_SCALE_MODE_FOXELS					= 0;						// Foxels, based on sysmetrics() average font width and height
	//const u32			_SCALE_MODE_INCHES					= 1;						// Inches, based on correlating inches to default dpi
	const u32			_SCALE_MODE_PIXELS					= 3;						// Pixels, based on individual pixels


//////////
// Fill style
//////
	const u32			_FILL_STYLE_SOLID					= 0;						// Solid fill
	const u32			_FILL_STYLE_TRANSPARENT				= 1;						// Transparent (no fill)
	const u32			_FILL_STYLE_HORIZONTAL				= 2;						// Horizontal lines
	const u32			_FILL_STYLE_VERTICAL				= 3;						// Vertical lines
	const u32			_FILL_STYLE_UL2LR_DIAGONAL			= 4;						// Upper-left to lower-right diagonal
	const u32			_FILL_STYLE_LL2UR_DIAGONAL			= 5;						// Lower-left to upper-right diagonal
	const u32			_FILL_STYLE_HORIZONTAL_AND_VERTICAL	= 6;						// Squares, both horizontal and vertical lines
	const u32			_FILL_STYLE_BOTH_DIAGONALS			= 7;						// Diamonds, both diagonal directions


//////////
// Special effects for rendering
//////
	const u32			_SPECIAL_EFFECT_DEFAULT				= 0;
	const u32			_SPECIAL_EFFECT_RAISED				= 0;
	const u32			_SPECIAL_EFFECT_PLAIN				= 1;
	const u32			_SPECIAL_EFFECT_SUNKEN				= 1;
	const u32			_SPECIAL_EFFECT_HOT_TRACKING		= 2;
	const u32			_SPECIAL_EFFECT_FLAT				= 2;
	const u32			_SPECIAL_EFFECT_TABS				= 10;
	const u32			_SPECIAL_EFFECT_CAROUSEL			= 11;


//////////
// Form windows
//////
	const u32			_WINDOW_STATE_NORMAL				= 0;						// Normal
	const u32			_WINDOW_STATE_MINIMIZED				= 1;						// Minimized
	const u32			_WINDOW_STATE_MAXIMIZED				= 2;						// Maximized

	const u32			_WINDOW_TYPE_MODELESS				= 0;						// Works in cooperation with other forms
	const u32			_WINDOW_TYPE_MODAL					= 1;						// The focus is limited to one form
	const u32			_WINDOW_TYPE_READ					= 2;						// The input is a READ window
	const u32			_WINDOW_TYPE_READ_MODAL				= 3;						// The input is a READ MODAL window


//////////
// Carousel types
//////
	const u32			_CAROUSEL_WINDOW_TYPE_RIDER			= 1;						// Only rider objects are allowed
	const u32			_CAROUSEL_WINDOW_TYPE_TOOLBAR		= 2;						// Only toolbar objects are allowed


//////////
// Rider types
//////
	const u32			_RIDER_WINDOW_TYPE_FIXED			= 1;						// Can only be fully displayed
	const u32			_RIDER_WINDOW_TYPE_SPINS			= 2;						// Allows spinning


//////////
// Toolbar class constants
//////
	const u32			_TOOLBAR_WIDTH_UNLIMITED			= -1;
	const u32			_TOOLBAR_STYLE_HORIZONTAL			= 1;
	const u32			_TOOLBAR_STYLE_VERTICAL				= 2;


//////////
// Object mouse pointers
//////
	const u32			_MOUSE_POINTER_DEFAULT				= 0;
	const u32			_MOUSE_POINTER_ARROW1				= 1;
	const u32			_MOUSE_POINTER_CROSS				= 2;
	const u32			_MOUSE_POINTER_I_BEAM				= 3;
	const u32			_MOUSE_POINTER_ICON					= 4;
	const u32			_MOUSE_POINTER_SIZE					= 5;
	const u32			_MOUSE_POINTER_SIZE_NE_SW			= 6;
	const u32			_MOUSE_POINTER_SIZE_NS				= 7;
	const u32			_MOUSE_POINTER_SIZE_NW_SE			= 8;
	const u32			_MOUSE_POINTER_SIZE_W_E				= 9;
	const u32			_MOUSE_POINTER_UP_ARROW				= 10;
	const u32			_MOUSE_POINTER_HOURGLASS			= 11;
	const u32			_MOUSE_POINTER_NO_DROP				= 12;
	const u32			_MOUSE_POINTER_HIDE_POINTER			= 13;
	const u32			_MOUSE_POINTER_ARROW2				= 14;
	const u32			_MOUSE_POINTER_HAND					= 15;
	const u32			_MOUSE_POINTER_DOWN_ARROW			= 16;
	const u32			_MOUSE_POINTER_MAGNIFYING_GLASS		= 17;
	const u32			_MOUSE_POINTER_CUSTOM				= 18;


//////////
// Drag mode
//////
	const u32			_DRAG_MODE_MANUAL					= 0;
	const u32			_DRAG_MODE_AUTOMATIC				= 1;


//////////
// OLE constants
//////
	const u32			_DROP_EFFECT_NONE					= 0;
	const u32			_DROP_EFFECT_COPY					= 1;
	const u32			_DROP_EFFECT_MOVE					= 2;
	const u32			_DROP_EFFECT_LINK					= 4;

	const u32			_DROP_HAS_DATA_AUTOMATIC			= -1;
	const u32			_DROP_HAS_DATA_NO					= 0;
	const u32			_DROP_HAS_DATA_YES					= 1;

	const u32			_DROP_DISABLED						= 0;
	const u32			_DROP_ENABLED						= 1;
	const u32			_DROP_TO_CONTAINER					= 2;

	const u32			_OLE_IS_ACTIVEX						= -2;
	const u32			_OLE_IS_BOUND_EMPTY					= -1;
	const u32			_OLE_IS_LINKED						= 0;
	const u32			_OLE_IS_EMBEDDED					= 1;


//////////
// Grid related
//////
	const u32			_GRID_PANEL_LEFT					= 0;
	const u32			_GRID_PANEL_RIGHT					= 1;

	const u32			_GRID_LINES_NONE					= 0;						// No grid lines (leave the background fill color)
	const u32			_GRID_LINES_HORIZONTAL				= 1;						// Horizontal lines only
	const u32			_GRID_LINES_VERTICAL				= 2;						// Vertical lines only
	const u32			_GRID_LINES_BOTH					= 3;						// Both horizontal and vertical

	const u32			_GRID_NO_PARTITION					= 0;
	const u32			_GRID_PARTITION						= 1;

	const u32			_GRID_RECORD_SOURCE_TABLE			= 0;
	const u32			_GRID_RECORD_SOURCE_ALIAS			= 1;
	const u32			_GRID_RECORD_SOURCE_PROMPT			= 2;
	const u32			_GRID_RECORD_SOURCE_QUERY			= 3;
	const u32			_GRID_RECORD_SOURCE_SQL				= 4;

	const u32			_GRID_ROW_COL_CHANGE_NONE			= 0;
	const u32			_GRID_ROW_COL_CHANGE_ROW			= 1;
	const u32			_GRID_ROW_COL_CHANGE_COL			= 2;

	const u32			_GRID_VIEW_BROWSE					= 0;
	const u32			_GRID_VIEW_CHANGE					= 1;
	const u32			_GRID_VIEW_CHANGE_LEFT				= 2;
	const u32			_GRID_VIEW_CHANGE_BOTH				= 3;


//////////
// Visual effects
//////
	const u32			_VISUAL_EFFECT_NONE					= 0;
	const u32			_VISUAL_EFFECT_RAISED				= 1;
	const u32			_VISUAL_EFFECT_DEPRESSED			= 2;


//////////
// Tabs on a pageframe
//////
	const u32			_TAB_ORIENTATION_TOP				= 0;
	const u32			_TAB_ORIENTATION_BOTTOM				= 1;
	const u32			_TAB_ORIENTATION_LEFT				= 2;
	const u32			_TAB_ORIENTATION_RIGHT				= 3;

	const u32			_TAB_STYLE_JUSTIFIED				= 0;
	const u32			_TAB_STYLE_UNJUSTIFIED				= 1;


//////////
// Date entry settings
//////
	const u32			_STRICT_DATE_LOOSE					= 0;
	const u32			_STRICT_DATE_STRICT					= 1;


//////////
// Common date functions constants
//////
	const u32			_DMY_COMMON_DAY						= 0;
	const u32			_DMY_COMMON_MONTH					= 1;
	const u32			_DMY_COMMON_YEAR					= 2;
	const u32			_DMY_COMMON_DMY						= 3;
	const u32			_DMY_COMMON_MDY						= 4;
	const u32			_DMY_COMMON_DTOS					= 5;


//////////
// Common time functions constants
//////
	const u32			_HMS_COMMON_HOUR					= 0;
	const u32			_HMS_COMMON_MINUTE					= 1;
	const u32			_HMS_COMMON_SECOND					= 2;
	const u32			_HMS_COMMON_MILLISECOND				= 3;
	const u32			_HMS_COMMON_MICROSECOND				= 4;


//////////
// Common xseconds functions constants
//////
	const u32			_XSECONDS_FUNCTION_NANOSECOND		= 1;
	const u32			_XSECONDS_FUNCTION_MICROSECOND		= 2;
	const u32			_XSECONDS_FUNCTION_SECONDS			= 3;
	const u32			_XSECONDS_FUNCTION_SECONDSX			= 4;


//////////
// Common conversion functions constants
//////
	const u32			_CONVERSION_FUNCTION_TIME			= 1;
	const u32			_CONVERSION_FUNCTION_TIMEX			= 2;
	const u32			_CONVERSION_FUNCTION_SECONDS		= 3;
	const u32			_CONVERSION_FUNCTION_SECONDSX		= 4;
	const u32			_CONVERSION_FUNCTION_DATE			= 5;
	const u32			_CONVERSION_FUNCTION_DATETIME		= 6;
	const u32			_CONVERSION_FUNCTION_DATETIMEX		= 7;


//////////
// Days of week, months of year
//////
	// These can be altered if/when languages are changed
	s8*					cgcDayOfWeekNames[7]						= { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	s8*					cgcMonthNames[12]							= { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	s8*					cgcDayOfWeekNamesShort[7]					= { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	s8*					cgcMonthNamesShort[12]						= { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };


//////////
// Stretch mode
//////
	const u32			_STRETCH_CLIP						= 0;
	const u32			_STRETCH_ISOMETRIC					= 1;
	const u32			_STRETCH_STRETCH					= 2;
	const u32			_STRETCH_SCROLL						= 3;


//////////
// Show window constants
//////
	const u32			_SHOW_WINDOW_IN_SCREEN				= 0;
	const u32			_SHOW_WINDOW_AS_CHILD				= 1;
	const u32			_SHOW_WINDOW_IN_OS					= 2;


//////////
// Seconds settings
//////
	const u32			_SECONDS_OFF						= 0;
	const u32			_SECONDS_ON							= 1;
	const u32			_SECONDS_SET						= 2;


//////////
// Scroll bars setting
//////
	const u32			_SCROLL_BARS_NONE					= 0;
	const u32			_SCROLL_BARS_HORIZONTAL				= 1;
	const u32			_SCROLL_BARS_VERTICAL				= 2;
	const u32			_SCROLL_BARS_BOTH					= 3;


//////////
// Row source types for listbox and combobox
//////
	const u32			_ROW_SOURCE_TYPE_NONE				= 0;
	const u32			_ROW_SOURCE_TYPE_VALUE				= 1;
	const u32			_ROW_SOURCE_TYPE_ALIAS				= 2;
	const u32			_ROW_SOURCE_TYPE_SQL				= 3;
	const u32			_ROW_SOURCE_TYPE_QUERY				= 4;
	const u32			_ROW_SOURCE_TYPE_ARRAY				= 5;
	const u32			_ROW_SOURCE_TYPE_FIELDS				= 6;
	const u32			_ROW_SOURCE_TYPE_FILES				= 7;
	const u32			_ROW_SOURCE_TYPE_STRUCTURE			= 8;
	const u32			_ROW_SOURCE_TYPE_POPUP				= 9;
	const u32			_ROW_SOURCE_TYPE_COLLECTION			= 10;


//////////
// Rotation for images
//////
	const u32			_ROTATE_NONE						= 0;
	const u32			_ROTATE_90							= 1;
	const u32			_ROTATE_180							= 2;
	const u32			_ROTATE_270							= 3;
	const u32			_ROTATE_NONE_FLIP					= 4;
	const u32			_ROTATE_90_FLIP						= 5;
	const u32			_ROTATE_180_FLIP					= 6;
	const u32			_ROTATE_270_FLIP					= 7;


//////////
// Release type
//////
	const u32			_RELEASE_TYPE_VARIABLE				= 0;
	const u32			_RELEASE_TYPE_CLOSE					= 1;
	const u32			_RELEASE_TYPE_QUIT					= 2;


//////////
// Picture constants
//////
	const u32			_PICTURE_LEFT_TOP					= 0;
	const u32			_PICTURE_LEFT_CENTERED				= 1;
	const u32			_PICTURE_LEFT_BOTTOM				= 2;
	const u32			_PICTURE_RIGHT_TOP					= 3;
	const u32			_PICTURE_RIGHT_CENTERED				= 4;
	const u32			_PICTURE_RIGHT_BOTTOM				= 5;
	const u32			_PICTURE_ABOVE_LEFT					= 6;
	const u32			_PICTURE_ABOVE_CENTERED				= 7;
	const u32			_PICTURE_ABOVE_RIGHT				= 8;
	const u32			_PICTURE_BELOW_LEFT					= 9;
	const u32			_PICTURE_BELOW_CENTERED				= 10;
	const u32			_PICTURE_BELOW_RIGHT				= 11;
	const u32			_PICTURE_CENTERED_TOP				= 12;
	const u32			_PICTURE_CENTERED_RELATIVE			= 13;
	const u32			_PICTURE_CENTERED_NO_TEXT3			= 14;

	const u32			_PICTURE_NO_DISPLAY					= 0;
	const u32			_PICTURE_CLIP						= 1;
	const u32			_PICTURE_SCALE						= 2;
	const u32			_PICTURE_STRETCH					= 3;


//////////
// Object clickEx click flags
//////
	const u32			_MOUSE_LEFT_BUTTON					= 1;
	const u32			_MOUSE_MIDDLE_BUTTON				= 2;
	const u32			_MOUSE_RIGHT_BUTTON					= 4;


//////////
// Object anchor mode bit masks
// Note:  If conflicting values are attempted, they are ignored.
//////
	const u32			_ANCHOR_FIXED_NORESIZE				= 0;
	const u32			_ANCHOR_TOP_ABSOLUTE				= 1;
	const u32			_ANCHOR_LEFT_ABSOLUTE				= 2;
	const u32			_ANCHOR_BOTTOM_ABSOLUTE				= 4;
	const u32			_ANCHOR_RIGHT_ABSOLUTE				= 8;
	const u32			_ANCHOR_TOP_RELATIVE				= 16;
	const u32			_ANCHOR_LEFT_RELATIVE				= 32;
	const u32			_ANCHOR_BOTTOM_RELATIVE				= 64;
	const u32			_ANCHOR_RIGHT_RELATIVE				= 128;
	const u32			_ANCHOR_DO_NOT_RESIZE_HORIZONTALLY	= 256;
	const u32			_ANCHOR_DO_NOT_RESIZE_VERTICALLY	= 512;


//////////
// Object property flags
//////
	const u32			_EMPTY								= 1;
	const u32			_FORM								= 2;
	const u32			_SUBFORM							= 4;
	const u32			_LABEL								= 8;
	const u32			_TEXTBOX							= 16;
	const u32			_BUTTON								= 32;
	const u32			_EDITBOX							= 64;
	const u32			_IMAGE								= 128;
	const u32			_CHECKBOX							= 256;
	const u32			_OPTION								= 512;
	const u32			_RADIO								= 1024;
	const u32			_ALL								= _EMPTY + _FORM + _SUBFORM + _LABEL + _TEXTBOX + _BUTTON + _EDITBOX + _IMAGE + _CHECKBOX + _OPTION + _RADIO;


//////////
// NCSET() Nuance Compatibility Settings
/////
	const u32			_NCSET_SIGN_SIGN2					= 1;
	const u32			_NCSET_CEILING_FLOOR				= 2;
	const u32			_NCSET_OPTIMIZE_TABLE_WRITES		= 3;
	const u32			_NCSET_OPTIMIZE_VARIABLES			= 4;
	const u32			_NCSET_RGBA_ALPHA_IS_OPAQUE			= 5;
	const u32			_NCSET_DATETIME_MILLISECONDS		= 6;
	const u32			_NCSET_DIRECT_NATIVE_MEMBERS		= 9;


//////////
// _settings validations
//////
	const u32			_MIN_SET_DECIMALS					= 0;
	const u32			_MAX_SET_DECIMALS					= 18;


//////////
// Math constants
//////
	const f64			_MATH_PI							= 3.141592653589793238;
	const f64			_MATH_PI2							= 1.570796326794896619;
	const f64			_MATH_PI180							= 0.017453292519943295;
	const f64			_MATH_180PI							= 57.29577951308232087;
	const f64			_MATH_2PI							= 6.283185307179586476;
	const f64			_MATH_EXP							= 2.718281828459045235;

//////////
// Common numeric functions constants
//////
	const u32			_FP_COMMON_SQRT						= 0;
	const u32			_FP_COMMON_EXP						= 1;
	const u32			_FP_COMMON_PI						= 2;
	const u32			_FP_COMMON_LOG						= 3;
	const u32			_FP_COMMON_LOG10					= 4;
	const u32			_FP_COMMON_CEILING					= 5;
	const u32			_FP_COMMON_FLOOR					= 6;
	const u32			_FP_COMMON_DTOR						= 7;
	const u32			_FP_COMMON_RTOD						= 8;
	const u32			_FP_COMMON_COS						= 9;
	const u32			_FP_COMMON_SIN						= 10;
	const u32			_FP_COMMON_ABS						= 11;
	const u32			_FP_COMMON_ACOS						= 12;
	const u32			_FP_COMMON_ASIN						= 13;
	const u32			_FP_COMMON_ATAN						= 14;
	const u32			_FP_COMMON_ATN2						= 15;
	const u32			_FP_COMMON_MOD						= 16;
	const u32			_FP_COMMON_FV						= 17;
	const u32			_FP_COMMON_PV						= 18;
	const u32			_FP_COMMON_PAYMENT					= 19;
	const u32			_FP_COMMON_TAN						= 20;


//////////
// Internal messages
//////
#ifdef WM_USER
	const u32			WMVJR_FIRST_CREATION				= WM_USER + 1;
#endif


//////////
// For tooltips, 20x per second
//////
	const u32			_TOOLTIP_TIMER_INTERVAL				= 250;
	const u32			_TOOLTIP_TIMER_DEFAULT_TIMEOUT		= 2500;		// 2.5 seconds


//////////
// DECLARE DLL constants
//////
	const s32			_DLL_TYPE_VP						= 1;
	const s32			_DLL_TYPE_VOID						= 2;
	const s32			_DLL_TYPE_S16						= 3;
	const s32			_DLL_TYPE_U16						= 4;
	const s32			_DLL_TYPE_S32						= 5;
	const s32			_DLL_TYPE_U32						= 6;
	const s32			_DLL_TYPE_F32						= 7;
	const s32			_DLL_TYPE_F64						= 8;
	const s32			_DLL_TYPE_S64						= 9;
	const s32			_DLL_TYPE_U64						= 10;
	const s32			_DLL_TYPE_STRING					= 11;
	const s32			_DLL_TYPE_IDISPATCH					= 12;
	const u32			_DLL_TYPE__byRef_postProcess		= 128;
	const s8			cgc_ret1[]							= "ret1";	// Variable name used for display in debuggers


//////////
// Internal variable names
//////
	const u8			cgcName_asciicols[]					= "_asciicols";
	const u8			cgcName_asciirows[]					= "_asciirows";
	const u8			cgcName_beautify[]					= "_beautify";
	const u8			cgcName_browser[]					= "_browser";
	const u8			cgcName_builder[]					= "_builder";
	const u8			cgcName_calcmem[]					= "_calcmem";
	const u8			cgcName_calcvalue[]					= "_calcvalue";
	const u8			cgcName_cliptext[]					= "_cliptext";
	const u8			cgcName_codesense[]					= "_codesense";
	const u8			cgcName_converter[]					= "_converter";
	const u8			cgcName_coverage[]					= "_coverage";
	const u8			cgcName_dblclick[]					= "_dblclick";
	const u8			cgcName_diarydate[]					= "_diarydate";
	const u8			cgcName_dos[]						= "_dos";
	const u8			cgcName_foxcode[]					= "foxcode";
	const u8			cgcName_foxref[]					= "_foxref";
	const u8			cgcName_foxtask[]					= "_foxtask";
	const u8			cgcName_gallery[]					= "_gallery";
	const u8			cgcName_genhtml[]					= "_genhtml";
	const u8			cgcName_genmenu[]					= "_genmenu";
	const u8			cgcName_getexpr[]					= "_getexpr";
	const u8			cgcName_incseek[]					= "_incseek";
	const u8			cgcName_include[]					= "_include";
	const u8			cgcName_mac[]						= "_mac";
	const u8			cgcName_meta1[]						= "_meta1";
	const u8			cgcName_meta2[]						= "_meta2";
	const u8			cgcName_meta3[]						= "_meta3";
	const u8			cgcName_meta4[]						= "_meta4";
	const u8			cgcName_meta5[]						= "_meta5";
	const u8			cgcName_meta6[]						= "_meta6";
	const u8			cgcName_meta7[]						= "_meta7";
	const u8			cgcName_meta8[]						= "_meta8";
	const u8			cgcName_meta9[]						= "_meta9";
	const u8			cgcName_mline[]						= "_mline";
	const u8			cgcName_objectbrowser[]				= "_objectbrowser";
	const u8			cgcName_pageno[]					= "_pageno";
	const u8			cgcName_pagetotal[]					= "_pagetotal";
	const u8			cgcName_pretext[]					= "_pretext";
	const u8			cgcName_reportbuilder[]				= "_reportbuilder";
	const u8			cgcName_reportoutput[]				= "_reportoutput";
	const u8			cgcName_reportpreview[]				= "_reportpreview";
	const u8			cgcName_samples[]					= "_samples";
	const u8			cgcName_scctext[]					= "_scctext";
	const u8			cgcName_shell[]						= "_shell";
	const u8			cgcName_spellchk[]					= "_spellchk";
	const u8			cgcName_startup[]					= "_startup";
	const u8			cgcName_startupTime[]				= "_startupTime";
	const u8			cgcName_tasklist[]					= "_tasklist";
	const u8			cgcName_taskpane[]					= "_taskpane";
	const u8			cgcName_tally[]						= "_tally";
	const u8			cgcName_text[]						= "_text";
	const u8			cgcName_throttle[]					= "_throttle";
	const u8			cgcName_toolbox[]					= "_toolbox";
	const u8			cgcName_triggerlevel[]				= "_triggerlevel";
	const u8			cgcName_unix[]						= "_unix";
	const u8			cgcName_vfp[]						= "_vfp";
	const u8			cgcName_windows[]					= "_windows";
	const u8			cgcName_wizard[]					= "_wizard";



//////////
// Base class control names
//////
	const u8			cgcName_empty[]						= "empty";
	const u8			cgcName_form[]						= "form";
	const u8			cgcName_subform[]					= "subform";
	const u8			cgcName_carousel[]					= "carousel";
	const u8			cgcName_rider[]						= "rider";
	const u8			cgcName_label[]						= "label";
	const u8			cgcName_textbox[]					= "textbox";
	const u8			cgcName_button[]					= "button";
	const u8			cgcName_editbox[]					= "editbox";
	const u8			cgcName_image[]						= "image";
	const u8			cgcName_checkbox[]					= "checkbox";
	const u8			cgcName_option[]					= "option";
	const u8			cgcName_radio[]						= "radio";
	const u8			cgcName_cmdgroup[]					= "commandgroup";
	const u8			cgcName_optgroup[]					= "optiongroup";
	const u8			cgcName_listbox[]					= "listbox";
	const u8			cgcName_combobox[]					= "combobox";
	const u8			cgcName_formset[]					= "formset";
	const u8			cgcName_toolbar[]					= "toolbar";
	const u8			cgcName_separator[]					= "separator";
	const u8			cgcName_line[]						= "line";
	const u8			cgcName_shape[]						= "shape";
	const u8			cgcName_container[]					= "container";
	const u8			cgcName_control[]					= "control";
	const u8			cgcName_grid[]						= "grid";
	const u8			cgcName_column[]					= "column";
	const u8			cgcName_header[]					= "header";
	const u8			cgcName_olebound[]					= "olebound";
	const u8			cgcName_olecontain[]				= "olecontainer";
	const u8			cgcName_spinner[]					= "spinner";
	const u8			cgcName_timer[]						= "timer";
	const u8			cgcName_hyperlink[]					= "hyperlink";
	const u8			cgcName_collection[]				= "collection";
	const u8			cgcName_page[]						= "page";
	const u8			cgcName_pageframe[]					= "pageframe";
	const u8			cgcName_session[]					= "session";
	const u8			cgcName_custom[]					= "custom";
	const u8			cgcName_exception[]					= "exception";
	const u8			cgcName_settings[]					= "_settings";

	// Various captions
	const u8			cgcName_formCaption[]				= "VJr Form";
	const u8			cgcName_carouselCaption[]			= "Carousel";


//////////
// Internal variable names
//////       
     const u8			cgcName_alignment[]					= "_alignment";
     const u8			cgcName_assist[]					= "_assist";
     const u8			cgcName_box[]						= "_box";
     const u8			cgcName_curobj[]					= "_curobj";
     const u8			cgcName_foxdoc[]					= "_foxdoc";
     const u8			cgcName_foxgraph[]					= "_foxgraph";
     const u8			cgcName_gengraph[]					= "_gengraph";
     const u8			cgcName_genpd[]						= "_genpd";
     const u8			cgcName_genscrn[]					= "_genscrn";
     const u8			cgcName_genxtab[]					= "_genxtab";
     const u8			cgcName_indent[]					= "_indent";
     const u8			cgcName_lmargin[]					= "_lmargin";
     const u8			cgcName_menudesigner[]				= "_menudesigner";
     const u8			cgcName_padvance[]					= "_padvance";
     const u8			cgcName_pbpage[]					= "_pbpage";
     const u8			cgcName_pcolno[]					= "_pcolno";
     const u8			cgcName_pcopies[]					= "_pcopies";
     const u8			cgcName_pdriver[]					= "_pdriver";
     const u8			cgcName_pdsetup[]					= "_pdsetup";
     const u8			cgcName_pecode[]					= "_pecode";
     const u8			cgcName_peject[]					= "_peject";
     const u8			cgcName_pepage[]					= "_pepage";
     const u8			cgcName_plength[]					= "_plength";
     const u8			cgcName_plineno[]					= "_plineno";
     const u8			cgcName_ploffset[]					= "_ploffset";
     const u8			cgcName_ppitch[]					= "_ppitch";
     const u8			cgcName_pquality[]					= "_pquality";
     const u8			cgcName_pscode[]					= "_pscode";
     const u8			cgcName_pspacing[]					= "_pspacing";
     const u8			cgcName_pwait[]						= "_pwait";
     const u8			cgcName_rmargin[]					= "_rmargin";
     const u8			cgcName_runactivedoc[]				= "_runactivedoc";
     const u8			cgcName_tabs[]						= "_tabs";
     const u8			cgcName_tooltiptimeout[]			= "_tooltiptimeout";
     const u8			cgcName_transport[]					= "_transport";
     const u8			cgcName_wrap[]						= "_wrap";


//////////
// Some BXML property settings
//////
	// Bxml tag names
	const s8			cgcTag_jdebi[]						= "jdebi";
	const s8			cgcTag_source_code[]				= "source_code";
	const s8			cgcTag_icons[]						= "icons";
	const s8			cgcTag_icon[]						= "icon";
	const s8			cgcTag_toolbars[]					= "toolbars";
	const s8			cgcTag_toolbar[]					= "toolbar";
	const s8			cgcTag_separator[]					= "separator";
	// Attribute tag names
	const s8			cgcTag_vertical[]					= "vertical";
	const s8			cgcTag_horizontal[]					= "horizontal";
	const s8			cgcTag_layout[]						= "layout";
	const s8			cgcTag_name[]						= "name";
	const s8			cgcTag_value[]						= "val";
	const s8			cgcTag_typeDetail[]					= "td";
	const s8			cgcTag_object[]						= "obj";
	const s8			cgcTag_baseclass[]					= "bc";
	const s8			cgcTag_class[]						= "c";
	const s8			cgcTag_classLibrary[]				= "cl";
	const s8			cgcTag_p[]							= "p";			// Fixed properties
	const s8			cgcTag_props[]						= "props";		// Class properties container
	const s8			cgcTag_prop[]						= "prop";		// Class property
	const s8			cgcTag_h[]							= "h";			// Height
	const s8			cgcTag_x[]							= "x";			// X
	const s8			cgcTag_y[]							= "y";			// Y
	const s8			cgcTag_w[]							= "w";			// Width
	const s8			cgcTag_width[]						= "width";
	const s8			cgcTag_height[]						= "height";
	const s8			cgcTag_iconWidth[]					= "iconwidth";
	const s8			cgcTag_iconHeight[]					= "iconheight";
	const s8			cgcTag_visible[]					= "visible";


//////////
// Default values for various types
//////
	const u8			cgc_defaultNumeric[10]				= "0";
	const u8			cgc_defaultDate[]					= "        ";
	const u8			cgc_spaceText[]						= " ";
	const u8			cgcPointChar[]						= ".";
	const u8			cgcSeparatorChar[]					= ",";
	const u8			cgcComma[]							= ",";
	const u8			cgcDollarSign[]						= "$";
	const u8			cgc_space_pm_uppercase[]			= " PM";
	const u8			cgc_space_am_uppercase[]			= " AM";
	const u8			cgc_space_pm_lowercase[]			= " pm";
	const u8			cgc_space_am_lowercase[]			= " am";
	const u8			cgc_pm_uppercase[]					= "PM";
	const u8			cgc_am_uppercase[]					= "AM";
	const u8			cgc_pm_lowercase[]					= "pm";
	const u8			cgc_am_lowercase[]					= "am";


//////////
// Primary object names
//////
	const u8			cgcName_sourceCode[]				= "_sourcecode";
	const u8			cgcName_locals[]					= "_locals";
	const u8			cgcName_watch[]						= "_watch";
	const u8			cgcName_command[]					= "_cmd";
	const u8			cgcName_debug[]						= "_debug";
	const u8			cgcName_output[]					= "_output";
	const u8			cgcName_sourceLight[]				= "_sourcelight";
	const u8			cgcName_screen[]					= "_screen";
	const u8			cgcName_jdebi[]						= "_jdebi";


//////////
// Auto-added child object names
//////
	const u8			cgcName_icon[]						= "_icon";								// Forms automatically get an app icon
	const u8			cgcName_caption[]					= "_caption";							// Forms, subforms automatically get a caption
	const u8			cgcName_iconCarousel[]				= "_carousel";							// Carousels, get an icon to toggle between tabs and carousel mode
	const u8			cgcName_iconMove[]					= "_move";								// Forms automatically get a move button (to move any subforms within using bars)
	const u8			cgcName_iconMinimize[]				= "_minimize";							// Forms automatically get a minimize button
	const u8			cgcName_iconMaximize[]				= "_maximize";							// Forms automatically get a maximize button
	const u8			cgcName_iconClose[]					= "_close";								// Forms automatically get a close button

	// Scale icons
	const u8			cgcName_iconScaleUl[]				= "_scaleul";							// Upper-left scale icon
	const u8			cgcName_iconScaleUr[]				= "_scaleUr";							// Upper-right scale icon
	const u8			cgcName_iconScaleLr[]				= "_scaleLr";							// Lower-right scale icon
	const u8			cgcName_iconScaleLl[]				= "_scaleLl";							// Lower-left scale icon

	const u8			cgcName_checkboxImage[]				= "_cbimage";							// Checkboxes automatically get a checkbox image
	const u8			cgcName_checkboxLabel[]				= "_cblabel";							// Checkboxes automatically get a checkbox label


//////////
// Supported languages
//////
	const u8			cgcEnglish[]						= "en";									// English


//////////
// Constant strings
//////
	const u8			cgcMessageWindowClass[]				= "VJr.MessageWindow";
	const u8			cgcWindowClass[]					= "VJr.Window";
	const u8			cgcFocusHighlightClass[]			= "VJr.FocusWindow";
	const u8			cgcTooltipClass[]					= "VJr.TooltipWindow";
	const u8			cgcSplashClass[]					= "VJr.SplashWindow";
	const u8			cgcSourceCodeTitle[]				= "SourceCode";
	const u8			cgcLocalsTitle[]					= "Locals";
	const u8			cgcWatchTitle[]						= "Watch";
	const u8			cgcCommandTitle[]					= "Command";
	const u8			cgcDebugTitle[]						= "Debug";
	const u8			cgcOutputTitle[]					= "Output";
	const u8			cgcSourceLightTitle[]				= "SourceLight";
	const u8			cgcSystemLog[]						= "System Log";
	const u8			cgc_noMateFound[]					= "Mate not found";
	const u8			cgcVersionShort[]					= "Version 0.57";
#if !defined(_NONVJR_COMPILE)
	const u8			cgc_appName[]						= "Visual FreePro, Jr.";				// Used for Grace 3D's OpenGL window
#endif
#ifdef __GNUC__
	#ifndef __amd64
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.57 -- May.04.2015 -- GCC 32-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.57 -- May.04.2015 -- GCC 32-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 32-bit 00.57.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 32-bit 00.57.0001.9999 for Windows [May.04.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.57.3201.9999";
	#else
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.57 -- May.04.2015   -- GCC 64-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.57 -- May.04.2015 -- GCC 64-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 64-bit 00.57.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 64-bit 00.57.0001.9999 for Windows [May.04.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.57.6401.9999";
	#endif
#else
	#if !defined(__64_BIT_COMPILER__)
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.57 -- May.04.2015 -- MSVC 32-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.57 -- May.04.2015 -- MSVC 32-bit";
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 32-bit 00.57.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 32-bit 00.57.0001.9999 for Windows [May.04.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.57.3201.9999";
	#else
		const u8		cgcScreenTitle[]					= "Visual FreePro, Jr. Version 0.57 -- May.04.2015 -- MSVC 64-bit";
		const u8		cgcJDebiTitle[]						= "JDebi Debugger Version 0.57 -- May.04.2015 -- MSVC 64-bit";
		// VERSION() support
		const u8		cgcVersionText[]					= "Visual FreePro, Jr. 64-bit 00.57.0001.9999 for Windows";
		const u8		cgcVersion1Text[]					= "Visual FreePro, Jr. 64-bit 00.57.0001.9999 for Windows [May.04.2015 00:00:00] Product ID 31415-926-5358979-32384";
		const u8		cgcVersion4Text[]					= "00.57.6401.9999";
	#endif
#endif
	const s32			gnVersion5							= 57;	// Version 0.57
	const s32			gnVersion2							= 2;	// Professional
	const s32			gnVersion3							= 0;	// English
	const u8			cgcFontName_default[]				= "Ubuntu";
	const u8			cgcFontName_defaultFixed[]			= "Ubuntu Mono";
	const u8			cgcFontName_windowTitleBar[]		= "Ubuntu Condensed";
	const u8			cgcFontName_subwindowTitleBar[]		= "Ubuntu Condensed";
	const u8			cgcFontName_defaultTooltip[]		= "Ubuntu Condensed";
	const u8			cgcFontName_cask[]					= "Ubuntu Mono";

	const u8			cgcCommandHistoryFilename[]			= "command.vjr";
	const u8			cgcDefault[]						= "default";
	const u8			cgcFormfeed[]						= "formfeed";
	const u8			cgcFoxgraphFilename[]				= "foxgraph.exe";
	const u8			cgcFoxrefFilename[]					= "foxref.app";
	const u8			cgcFoxtaskFilename[]				= "foxtask.dbf";
	const u8			cgcFoxgalleryFilename[]				= "gallery.app";
	const u8			cgcGengraphFilename[]				= "gengraph.APP";
	const u8			cgcGenhtmlFilename[]				= "genhtml.prg";
	const u8			cgcGenmenuFilename[]				= "genmenu.prg";
	const u8			cgcGenscrnFilename[]				= "genscrn.prg";
	const u8			cgcNone[]							= "none";
	const u8			cgcReportBuilderFilename[]			= "reportbuilder.app";
	const u8			cgcReportOutputFilename[]			= "reportoutput.app";
	const u8			cgcReportPreviewFilename[]			= "reportpreview.app";
	const u8			cgcRunActiveDocFilename[]			= "runactd.prg";
	const u8			cgcSamples[]						= "samples\\";
	const u8			cgcScctextFilename[]				= "scctext.prg";
	const u8			cgcScreenDataFilename[]				= "screen.vjr";
	const u8			cgcSpellchkFilename[]				= "spellchk.app";
	const u8			cgcScreenLayoutFilename[]			= "layout.bxml";
	const u8			cgcStartupPrgFilename[]				= "startup.prg";
	const u8			cgcSoundStartupWav[]				= "startup_44100_f32.wav";
	const u8			cgcSystemLogFilename[]				= "system.log";
	const u8			cgcTasklistFilename[]				= "tasklist.prg";
	const u8			cgcTaskpaneFilename[]				= "taskpane.prg";
	const u8			cgcToolboxFilename[]				= "toolbox.app";
	const u8			cgcWizardFilename[]					= "wizard.app";
