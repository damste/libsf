//////////
//
// /libsf/utils/common/cpp/xml/xml.h
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

#pragma once



class XmlNode;		// Holds code to access parts of an XML structure, as in "/root/tag1(N)/tag2(N).attrib(name).value"
class XmlData;		// Holds a string item, which contains ASCII text and a length
class CXml;			// Holds a fully-qualified root XML object (every xml can be a root, or a child/sibling/parent, each is fully featured)

#define _XML_HEADER "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"

//////////
// Forward declarations
//////
	uptr 			xml_load_file									(cs8* filename);
	uptr 			xml_load_file									(s8* filename);
	uptr 			xml_load_file									(cu8* filename);
	uptr 			xml_load_file									(u8* filename);

	uptr 			xml_load										(cs8* buffer, u32 tnLength);
	uptr 			xml_load										(s8* buffer, u32 tnLength);
	uptr 			xml_load										(cu8* buffer, u32 tnLength);
	uptr 			xml_load										(u8* buffer, u32 tnLength);

	CXml*			xml_loadAs_cxml									(cs8* buffer, u32 tnLength);
	CXml*			xml_loadAs_cxml									(s8* buffer, u32 tnLength);
	CXml*			xml_loadAs_cxml									(cu8* buffer, u32 tnLength);
	CXml*			xml_loadAs_cxml									(u8* buffer, u32 tnLength);

	uptr 			xml_write_file									(uptr handle, s8* filename);
	uptr 			xml_write_file									(uptr handle, cs8* filename);
	uptr 			xml_write_file									(uptr handle, u8* filename);
	uptr 			xml_write_file									(uptr handle, cu8* filename);

	uptr 			xml_access_node									(uptr handle, s8* tcNode, s8* tcReturn_value, u32 tnReturn_value_length);
	bool			xml_access_node_bool							(uptr handle, s8* tcNode);
	uptr 			xml_access_node_integer							(uptr handle, s8* tcNode);
	f64				xml_access_node_f64								(uptr handle, s8* tcNode);
	void			iXml_load__skip_white_spaces					(s8* buffer, u32 tnOffset, u32& tnThis, u32 tnLength);
	void			iXml_load__attributes							(CXml* toTag, s8* buffer, u32 tnOffset, u32& tnThis, u32 tnLength);
	u32				iXml_write_file__write_tag						(int tfh, CXml* toTag);
	bool			iXml_write_file__write_item						(int tfh, s8* tcData, u32 tnLength, CXml* toAttribute, s8* tcOpenCharacters, s8* tcCloseCharacters);
	bool			iXml_write_file__write_attribute				(int tfh, CXml* toAttribute);
	XmlNode*		iXml_access_node__get_node_segments				(s8* tcNode, u32 tnMaxLength);
	u32				iXml_access_node__store_n						(s8* tcNode, u32 tnStart, u32& tnLength, u32 tnMaxLength);
	void			iXml_access_node__copy_data						(u32& tnCount, XmlData* toData, s8* tcReturn_value, u32 tnReturn_value_length);









//////////
//
// XML Node class, used for accessing data within an XML.
// Creates a type of link-list which points through the syntax provided for the xml_access_node()
// function.  This allows a dot-like arrangement for referencing data to be employed.
//
// Example:
//		/rdc/command(0).attrib(cmd).value
//
// Would reference the contents of the "cmd" attribute in the following XML snippet:

//
/////
	class XmlNode
	{
	public:
		XmlNode() : m_iterate(0), m_count(0), m_return_type(XmlNode::none), m_next(NULL), m_name(NULL), m_name_length(0) { }
		~XmlNode() { if (m_next) delete m_next; }

		enum return_type
		{
			none			= 0,
			data			= 1,
			cdata			= 2,
			attrib_name		= 3,
			attrib_value	= 4
		};

	// Mutators
		void		set_next(XmlNode* d)		{ m_next		= d;					}
		void		set_name(s8* n, u32 l)		{ m_name		= n; m_name_length = l;	}
		void		set_iterate(u32 i)			{ m_iterate		= i;					}
		void		set_count(u32 c)			{ m_count		= c;					}
		void		set_return_type(u32 rt)		{ m_return_type	= rt;					}

	// Accessors
		XmlNode*	get_next()					{ return(m_next);			}
		s8*			get_name()					{ return(m_name);			}
		u32			get_length()				{ return(m_name_length);	}
		u32			get_iterate()				{ return(m_iterate);		}
		u32			get_count()					{ return(m_count);			}
		u32			get_return_type()			{ return(m_return_type);	}


	private:
		XmlNode*	m_next;			// Pointer to next Node* in one-way linked list
		s8*			m_name;			// Node name pointed to, if NULL, then every item is matched
		u32			m_name_length;	// Length of the name pointed to by m_name
		u32			m_iterate;		// Iterate count through the current level
		u32			m_count;		// Scratch counter used while searching the source XML for the appropriate iterate
		u32			m_return_type;	// Return type specified, either
	};









//////////
//
// String holds a data item with a specified bit of text (data bytes), and an associated length.
// Each XML that's parsed has one of these for tag names, for attributes, for actual data or cdata within a node, etc.
//
/////
	class XmlData
	{
	public:
		XmlData() :	m_next(NULL),
						m_data(NULL),
						m_length(0)
		{
		}

		// Creates a null-terminated string
		XmlData(s8* tcData) :	m_next(NULL),
								m_data(NULL),
								m_length(0)
		{
			if (tcData)
			{
				m_length = (u32)strlen(tcData);
				m_data = (s8*)malloc(m_length);
				if (m_data)
					memcpy(m_data, tcData, m_length);
				else
					m_length = 0;	// Unable to allocate, data item does not exist
			}
		}

		// Creates a string of a specified length
		XmlData(s8* tcData, u32 tnLength) :	m_next(NULL),
												m_data(NULL),
												m_length(0)
		{
			if (tcData)
			{
				m_data = (s8*)malloc(tnLength);
				if (m_data)
				{
					memcpy(m_data, tcData, tnLength);
					m_length = tnLength;
				}
			}
		}

		~XmlData()							{ if (this && m_data) free(m_data); }

	// Setters
		void		set_data(s8* data)		{ if (this) m_data		= data;		}
		void		set_length(u32 length)	{ if (this) m_length	= length;	}
		void		set_next(XmlData* d)	{ if (this) m_next		= d;		}

	// Getters
		s8*			as_s8p()				{ if (this) return(m_data);			else return(0);		}
		u8*			as_u8p()				{ if (this) return((u8*)m_data);	else return(0);		}
		s32			as_s32()				{ if (this) return(atoi(m_data));	else return(0);		}
		u32			length()				{ if (this) return(m_length);		else return(0);		}
		XmlData*	next()					{ if (this) return(m_next);			else return(0);		}

		// Populates a datum with information for passing
		SDatum* as_datum(SDatum* d)
		{
			if (d)
			{
				d->data_s8	= m_data;
				d->length	= m_length;
			}
			return(d);
		}

		// Returns whether the value is set to the specified character
		bool is_value(s8 ch)
		{
			// See if this is at least a one-digit field, and if so, if the first position matches our field
			if (this && m_length >= 1 && m_data[0] == ch)
				return(true);

			return(false);
		}

		bool is_value_ignore_case(s8 ch)
		{
			s8 chLower;

			// See if this is at least a one-digit field
			if (this && m_length >= 1)
			{
				// Grab our second character
				if (ch >= 'A' && ch <= 'Z')		chLower = ch + 0x20;
				else							chLower = ch;

				// See if it matches either one
				if (m_data[0] == ch || m_data[0] == chLower)
					return(true);
			}

			return(false);
		}


	// Duplicators
		XmlData* copy(void)
		{
			XmlData* d = NULL;
			s8* new_data;


			if (this)
			{
				// We check this condition for NULL because some functions call the copy() method using a get_attribute()->get_data()->copy() as one operation, and the get_data() returned was NULL
				d = new XmlData();
				if (m_data)
				{
					new_data = (s8*)malloc(m_length);
					if (new_data)
						memcpy(new_data, m_data, m_length);
					d->set_data(new_data);
					d->set_length(m_length);
				}
			}
			return(d);
		}


	private:
		XmlData*	m_next;			// Pointer to next XMLData* in one-way linked list
		s8*			m_data;			// Data to store here (pointer to existing data only, data is not copied)
		u32			m_length;		// Length of the data there
	};
	typedef XmlData* XmlDatap;









//////////
//
// Xml holds the base structure defining an XML.
// When xml_load() is called, it returns a handle to the XMLTag*, which is the root node.
// Each XML that's parsed has the root node, which actually then points as its first child to the real root node of the parsed XML file.
//
/////
	class CXml
	{
	public:
		CXml(s8* tcTag = NULL, u32 tnTagLength = -1, s8* tcData = NULL, u32 tnDataLength = -1, s8* tcAttributeTag = NULL, s8* tcAttributeData = NULL, u32 tnAttributeDataLength = -1) :
				   m_prev(NULL),
				   m_parent(NULL),
				   m_next(NULL),
				   m_child(NULL),
				   m_attribute(NULL),
				   m_tag(NULL),
				   m_data(NULL),
				   m_cdata(NULL),
				   m_closed(false)
		{
			CXml* tNewTag;
			XmlData* dNew;


			// If the user specifies some option, it creates those items as well
			if (tcTag)
			{
				// Store the tag and the data
				if (tnTagLength == (u32)-1)
					tnTagLength = (s32)strlen(tcTag);

				dNew = new XmlData(tcTag, tnTagLength);
				set_tag(dNew);
			}

			if (tcData)
			{
				if (tnDataLength == (u32)-1)
					tnDataLength = (s32)strlen(tcData);

				dNew = new XmlData(tcData, tnDataLength);
				set_data(dNew);
			}

			if (tcAttributeTag)
			{
				tNewTag = new CXml();
				tNewTag->set_tag(new XmlData(tcAttributeTag));

				if (tcAttributeData)
				{
					if (tnAttributeDataLength == (u32)-1)
						tnAttributeDataLength = (s32)strlen(tcAttributeData);

					tNewTag->set_data(new XmlData(tcAttributeData, tnAttributeDataLength));
				}

				set_attribute(tNewTag);
			}
		}

		CXml(XmlData* tdTag, XmlData* tdData = NULL, CXml* ttAttribute = NULL) :
				   m_prev(NULL),
				   m_parent(NULL),
				   m_next(NULL),
				   m_child(NULL),
				   m_attribute(NULL),
				   m_tag(NULL),
				   m_data(NULL),
				   m_cdata(NULL),
				   m_closed(false)
		{
			if (tdTag)
				set_tag(tdTag);

			if (tdData)
				set_data(tdData);

			if (ttAttribute)
				set_attribute(ttAttribute);
		}

		~CXml()
		{
			if (this)
			{
				Delete();

				if (m_next)
					delete m_next;

				if (m_child)
					delete m_child;

				if (m_attribute)
					delete m_attribute;

				if (m_tag)
					delete m_tag;

				if (m_data)
					delete m_data;

				if (m_cdata)
					delete m_cdata;
			}
		}

		void Delete(void)
		{
			if (this)
			{
				// Delete any children or dependencies
				if (m_next)
				{
					m_next->Delete();
					m_next = NULL;
				}

				if (m_child)
				{
					m_child->Delete();
					m_child = NULL;
				}

				if (m_attribute)
				{
					m_attribute->Delete();
					m_attribute = NULL;
				}
			}
		}

		CXml* append_child(CXml* tNew)
		{
			CXml* tChild;


			if (this)
			{
				if (child())
				{
					// We have to append to the end of the child tags
					tChild = child();
					while (tChild->next())
						tChild = tChild->next();

					// Append to the end of this chain
					tNew->set_parent(this);
					tChild->set_next(tNew);

				}
				else
				{
					// First child, we append here
					tNew->set_parent(this);
					set_child(tNew);

				}
				// All done, return the added tag
				return(tNew);
			}
			return(NULL);
		}

		CXml* append_next(CXml* tNew)
		{
			CXml* tNext;


			if (this)
			{
				if (next())
				{
					// We have to append to the end of the next tags
					tNext = next();
					while (tNext->next())
						tNext = tNext->next();

					// Append to the end of this chain
					tNew->set_prev(this);
					tNext->set_next(tNew);

				}
				else
				{
					// No item after this one, we append here
					tNew->set_prev(this);
					set_next(tNew);

				}
				// All done, return the added tag
				return(tNew);
			}
			return(NULL);
		}

		CXml* append_attribute(s8* tcTag, u32 tnTagLength, s8* tcData, u32 tnDataLength)
		{
			CXml* tNew;
			CXml* tNext;


			if (this)
			{
				// Create the new tag
				tNew = new CXml(tcTag, tnTagLength, tcData, tnDataLength);


				// See where we add it
				if (attribute())
				{
					// We have to append to the end of the next tags
					tNext = attribute();
					while (tNext->attribute())
						tNext = tNext->attribute();

					// Append to the end of this chain
					tNew->set_parent(this);
					tNext->set_attribute(tNew);

				}
				else
				{
					// No item after this one, we append here
					tNew->set_parent(this);
					set_attribute(tNew);

				}
				// All done, return the added tag
				return(tNew);
			}
			return(NULL);
		}
		CXml* append_attribute(const s8* tcTag, const s8* tcData)	{	return(append_attribute((s8*)tcTag, -1, (s8*)tcData, -1));		}
		CXml* append_attribute(const s8* tcTag, s8* tcData)			{	return(append_attribute((s8*)tcTag, -1,      tcData, -1));		}
		CXml* append_attribute(s8* tcTag, const s8* tcData)			{	return(append_attribute(     tcTag, -1, (s8*)tcData, -1));		}
		CXml* append_attribute(s8* tcTag, s8* tcData)				{	return(append_attribute(     tcTag, -1,      tcData, -1));		}

		CXml* append_attribute(XmlData* tcTag, XmlData* tcData)
		{
			CXml*	tNew;
			CXml*	tNext;


			if (this)
			{
				// Create the new tag
				tNew = new CXml(tcTag, tcData);


				// See where we add it
				if (attribute())
				{
					// We have to append to the end of the next tags
					tNext = attribute();
					while (tNext->attribute())
						tNext = tNext->attribute();

					// Append to the end of this chain
					tNew->set_parent(this);
					tNext->set_attribute(tNew);

				}
				else
				{
					// No item after this one, we append here
					tNew->set_parent(this);
					set_attribute(tNew);

				}
				// All done, return the added tag
				return(tNew);
			}
			return(NULL);
		}

		CXml* append_attribute(CXml* tNew)
		{
			CXml* tNext;


			if (this)
			{
				if (m_attribute)
				{
					// We have to append to the end of the next tags
					tNext = m_attribute;
					while (tNext->attribute())
						tNext = tNext->attribute();

					// Append to the end of this chain
					tNew->set_parent(this);
					tNext->set_attribute(tNew);

				}
				else
				{
					// No item after this one, we append here
					tNew->set_parent(this);
					set_attribute(tNew);

				}
				// All done, return the added tag
				return(tNew);
			}
			return(NULL);
		}


	// Mutators
		void			set_prev(CXml* t)				{ if (this) m_prev		= t;		}
		void			set_parent(CXml* t)				{ if (this) m_parent	= t;		}
		void			set_next(CXml* t)				{ if (this) m_next		= t;		}
		void			set_child(CXml* t)				{ if (this) m_child		= t;		}
		void			set_tag(XmlData* t)				{ if (this) m_tag		= t;		}
		void			set_data(XmlData* t)			{ if (this) m_data		= t;		}
		void			set_cdata(XmlData* t)			{ if (this) m_cdata		= t;		}
		void			set_closed(void)				{ if (this) m_closed	= true;		}
		void			set_open(void)					{ if (this) m_closed	= false;	}

		CXml* set_attribute(CXml* t)
		{
			u32 lnLength;
			CXml* tSearch;


			if (this)
			{
				if (m_attribute)
				{
					// Search through attributes to see if a matching attribute tag is found
					// If so, we replace its contents with the new one
					lnLength	= t->data()->length();
					tSearch		= m_attribute;
					while (tSearch->attribute())
					{
						if (tSearch->tag()->length() == lnLength)
						{
							// Same length, possible match
							if (_memicmp(tSearch->tag()->as_s8p(), t->tag()->as_s8p(), lnLength) == 0)
							{
								// It was a match, this is the one they're replacing
								// Update its pointer to point to the new thing
								t->append_attribute(tSearch->attribute());	// We append because this tag could have a whole slew of attributes behind it

								// The old attribute is no longer needed
								delete tSearch;

								// Done
								return(t);

							}
						}
						tSearch = tSearch->attribute();
					}
					// If we get here, it wasn't found, append it
					tSearch->set_attribute(t);

				}
				else
				{
					// First one
					t->set_parent(this);
					m_attribute	= t;

				}
				return(t);

			}
			return(NULL);
		}


		XmlData* set_attribute_data(const s8* tcTag, XmlData* t)	{	return(set_attribute_data((s8*)tcTag, t));		}
		XmlData* set_attribute_data(s8* tcTag, XmlData* t)
		{
			u32 lnLength;
			CXml* tSearch;


			if (this)
			{
				if (m_attribute)
				{
					// Search through attributes to see if a matching attribute tag is found
					// If so, we replace its contents with the new one
					lnLength	= (u32)strlen(tcTag);
					tSearch		= m_attribute;
					while (tSearch->attribute())
					{
						if (tSearch->tag()->length() == lnLength)
						{
							// Same length, possible match
							if (_memicmp(tSearch->tag()->as_s8p(), tcTag, lnLength) == 0)
							{
								// It was a match, this is the one they're updating
								if (tSearch->data())
									delete tSearch->data();

								// Update its pointer to point to the new thing
								tSearch->set_data(t);

								// Done
								return(t);

							}
						}
						tSearch = tSearch->attribute();
					}
					// If we get here, it wasn't found
					// We append it to the end
					append_attribute(new CXml(new XmlData(tcTag), t));

				}
			}
			return(NULL);
		}


	// Accessors
		CXml*			prev()						{ if (this) return(m_prev);			else return(NULL); }
		CXml*			parent()					{ if (this) return(m_parent);		else return(NULL); }
		CXml*			next()						{ if (this) return(m_next);			else return(NULL); }
		CXml*			child()						{ if (this) return(m_child);		else return(NULL); }
		CXml*			attribute()					{ if (this) return(m_attribute);	else return(NULL); }
		XmlData*		tag()						{ if (this) return(m_tag);			else return(NULL); }
		XmlData*		data()						{ if (this) return(m_data);			else return(NULL); }
		XmlData*		cdata()						{ if (this) return(m_cdata);		else return(NULL); }
		bool			is_closed()					{ if (this) return(m_closed);		else return(NULL); }


	// Functions
		s32 childCount(void)
		{
			s32		lnCount;
			CXml*	child;

			lnCount = 0;
			if (this)
			{
				// Count through each child
				for (child = this->child(); child; child = child->next())
					++lnCount;
			}

			// Indicate our count
			return(lnCount);
		}

		CXml* child(cu8* text)		{	return(child((s8*)text));			}
		CXml* child(cs8* text)		{	return(child((s8*)text));			}
		CXml* child(s8* text)
		{
			u32 lnLength;
			CXml* child;

			lnLength = (u32)strlen(text);
			child = this->child();
			while (child)
			{
				if (child->tag()->length() == lnLength)
				{
					// They're the same length, it's possible
					if (_memicmp(child->tag()->as_s8p(), text, lnLength) == 0)
					{
						// It's a match
						return(child);
					}
				}
				// Move to next child/sibling
				child = child->next();
			}
			// Not found it we get here
			return(NULL);
		}

		CXml* attribute(const s8* text)		{	return(attribute((s8*)text));			}
		CXml* attribute(s8* text)
		{
			u32 lnLength;
			CXml* attr;

			lnLength	= (u32)strlen(text);
			attr	= this->attribute();
			while (attr)
			{
				if (attr->tag()->length() == lnLength)
				{
					// They're the same length, it's possible
					if (_memicmp(attr->tag()->as_s8p(), text, lnLength) == 0)
					{
						// It's a match
						return(attr);
					}
				}
				// Move to next attribute/sibling
				attr = attr->attribute();
			}
			// Not found it we get here
			return(NULL);
		}

		bool tagEquals(const s8* text)		{	return(tagEquals((s8*)text));			}
		bool tagEquals(s8* text)
		{
			u32 lnLength;

			lnLength = (u32)strlen(text);
			if (tag()->length() == lnLength)
			{
				// They're the same length, it's possible
				if (_memicmp(tag()->as_s8p(), text, lnLength) == 0)
				{
					// It's a match
					return(true);
				}
			}
			return(false);
		}

		bool dataEquals(const s8* text)		{	return(dataEquals((s8*)text));			}
		bool dataEquals(s8* text)
		{
			u32 lnLength;

			lnLength = (u32)strlen(text);
			if (data()->length() == lnLength)
			{
				// They're the same length, it's possible
				if (memcmp(data()->as_s8p(), text, lnLength) == 0)
				{
					// It's a match
					return(true);
				}
			}
			return(false);
		}

		bool dataEqualsIgnoreCase(const s8* text)		{	return(dataEqualsIgnoreCase((s8*)text));			}
		bool dataEqualsIgnoreCase(s8* text)
		{
			u32 lnLength;

			lnLength = (u32)strlen(text);
			if (data()->length() == lnLength)
			{
				// They're the same length, it's possible
				if (_memicmp(data()->as_s8p(), text, lnLength) == 0)
				{
					// It's a match
					return(true);
				}
			}
			return(false);
		}

		CXml* copy(bool tlCopyAttributes = false, bool tlCopyChildren = false)
		{
			if (this)
			{
				CXml* tNew = new CXml(this->tag()->copy(), this->data()->copy());
				if (this->cdata())
					tNew->set_cdata(this->cdata()->copy());


				// Copy the attributes
				if (tlCopyAttributes)
					tNew->copy_attributes(this->attribute());


				// Copy the child nodes
				if (tlCopyChildren)
					tNew->copy_children(this->child());


				// Finished
				return(tNew);
			}
			return(NULL);
		}

		void copy_children(CXml* tc)
		{
			if (this && tc)
			{
				// Iterate until there are no more children to add
				CXml* tNewChild = new CXml(tc->tag()->copy(), tc->data()->copy());
				append_child(tNewChild);


				// Copy whatever is required to duplicate this item
				if (tc->cdata())
					tNewChild->set_cdata(tc->cdata()->copy());


				// Copy attributes and any of the specified's children
				tNewChild->copy_attributes	(tc->attribute());
				tNewChild->copy_children	(tc->child());
			}
		}


		void copy_attributes(CXml* ta)
		{
			if (this)
			{
				while (ta)
				{
					// Attributes are easy to copy, because all they ever have is a name and the data item, which is "name='data'"
					append_attribute(new CXml(ta->attribute()->tag()->copy(), ta->attribute()->data()->copy()));

					// Move to next attribute
					ta = ta->attribute();
				}
				// When we get here we have copied all attributes
			}
		}


		uptr save(const s8* tcFilename)	{	return(save((s8*)tcFilename));			}
		uptr save(s8* tcFilename = NULL, s8** tcOut = NULL, CXml* t = NULL)
		{
			s32 lnLevel = 0;
			s32 lnResult = 0;
			int lfh;


			if (tcFilename)
			{
				lfh = _sopen(tcFilename, _O_CREAT | _O_BINARY | _O_TRUNC | _O_RDWR, _SH_DENYRW, _S_IREAD | _S_IWRITE);
				if (lfh)
				{
//////////
// TODO: The code for load needs to know to look for this, until then we don't save it and just leave it off
//					// Write the header
//					_write(lfh, _XML_HEADER, sizeof(_XML_HEADER) - 1);
//////
					// Write everything below this level
					save__go(lfh, NULL, t ? t : this, lnResult, lnLevel);	// Write it to the file
					_close(lfh);
				}
			}

			if (tcOut)
			{
				if (!*tcOut)
				{
					// Find out how big it is
					save__go(0, NULL, t ? t : this, lnResult, lnLevel);

					// Allocate that much space
					*tcOut = (s8*)malloc(lnResult);
					lnResult = 0;
				}

				if (*tcOut)
					save__go(0, tcOut, t ? t : this, lnResult, lnLevel);		// Copy it to the buffer
			}

			// If we get here and both weren't defined, they would've not gone through the if-blocks above
			// If that's the case, they want to know how big it is (to allocate memory themselves)
			if (!tcFilename && !tcOut)
				save__go(0, NULL, t ? t : this, lnResult, lnLevel);	// Find out how big it is

			return(lnResult);
		}


private:
		uptr save__go(int tfh, s8** tcOut, CXml* t, s32& tnFileLength, s32& tnLevel)
		{
			// This function is called iteratively, so we increment the level each time
			++tnLevel;
			while (t)
			{
				// Write items in this order:
				//	1)	Tag + attributes
				//	2)	Data or CDATA
				//	3)	Child
				//	4)	Closing tag
				//	4)	Next
				if (t->data() || t->cdata() || t->child())
				{
					// Write tag
					if (!save__write_item(tfh, tcOut, t->tag()->as_s8p(), t->tag()->length(), t->attribute(), (s8*)"<", (s8*)">", tnFileLength))
					{
						// An error writing
						--tnLevel;
						return(-2);
					}

					// Write data
					if (t->data())
					{
						// Write data section
						if (!save__write_item(tfh, tcOut, t->data()->as_s8p(), t->data()->length(), NULL, (s8*)"", (s8*)"", tnFileLength))
						{
							// An error writing
							--tnLevel;
							return(-2);
						}

					}

					// Write CDATA
					if (t->cdata())
					{
						// Write CDATA section
						if (!save__write_item(tfh, tcOut, t->cdata()->as_s8p(), t->cdata()->length(), NULL, (s8*)"<![CDATA[", (s8*)"]]>", tnFileLength))
						{
							// An error writing
							--tnLevel;
							return(-2);
						}

					}

					// Write child entries
					if (t->child())
					{
						// Write child portion
						if (save__go(tfh, tcOut, t->child(), tnFileLength, tnLevel) != 0)
						{
							// Some error occurred
							--tnLevel;
							return(-2);
						}
					}

					// Write closing tag
					if (!save__write_item(tfh, tcOut, t->tag()->as_s8p(), t->tag()->length(), NULL, (s8*)"</", (s8*)">", tnFileLength))
					{
						// An error writing
						--tnLevel;
						return(-2);
					}

				//	1)	Tag + attributes in closing tag
				//	2)	Next
				} else if (t->attribute()) {
					// It's something <like this='x'/>
					if (!save__write_item(tfh, tcOut, t->tag()->as_s8p(), t->tag()->length(), t->attribute(), (s8*)"<", (s8*)"/>", tnFileLength))
					{
						// An error writing
						--tnLevel;
						return(-2);
					}

				} else {
					// It's just a single tag
					// It should have no children, no data, no cdata, no attributes
					if (!save__write_item(tfh, tcOut, t->tag()->as_s8p(), t->tag()->length(), t->attribute(), (s8*)"<", (s8*)"/>", tnFileLength))
					{
						// An error writing
						--tnLevel;
						return(-2);
					}

				}

				// Move to next item
				t = t->next();
			}

			// Decrement the level operator and see where we are
			--tnLevel;
			if (tnLevel == 0)
			{
				// We're done, this is the highest level
				// Append a NULL at the end to the string
				if ((tcOut && *tcOut) || (!tfh && !tcOut))
				{
					// When we return the length, we allow for the extra NULL at the end for the memory variable they'll be creating
					if (tcOut && *tcOut)
						(*tcOut)[tnFileLength] = 0;	// Actually write the NULL
					++tnFileLength;
				}
				//else, if they specified tfh, then we write the exact number of bytes
			}

			// No errors
			return(0);
		}


		// Writes data like "<" + tcData + ">"
		bool save__write_item(int tfh, s8** tcOut, s8* tcData, u32 tnLength, CXml* a, s8* tcOpenCharacters, s8* tcCloseCharacters, s32& tnFileLength)
		{
			u32 lnI, numread1, numread2, numread3;


			// See if there's anything
			if (tcData && tnLength != 0)
			{
				//////////
				// FIXUP HACK for XML syntax requirements
				// Converts < and > to << and >> ascii characters 171, 187
				/////
					// See if there are any characters which need conversion
					for (lnI = 0; lnI < tnLength; lnI++)
					{
						if (tcData[lnI] == '<')
							tcData[lnI] = (s8)0xab;	// Convert to << character
						if (tcData[lnI] == '>')
							tcData[lnI] = (s8)0xbb;	// Convert to >> character
						// Note:  This fixup code must be undone in xml_load (see xml.cpp's xml_load() function)
					}

				// Write this data
				if (tfh)
				{
					numread1 = _write(tfh, tcOpenCharacters, (u32)strlen(tcOpenCharacters));
					numread2 = _write(tfh, tcData, tnLength);
					if (numread1 != (u32)strlen(tcOpenCharacters) || numread2 != tnLength)
					{
						// Some error writing
						return(false);
					}
				}

				//////////
				// FIXUP HACK for XML syntax requirements
				// Converts << and >> back to < and >
				/////
					// Fix them back-up if they were there
					for (lnI = 0; lnI < tnLength; lnI++)
					{
						if (tcData[lnI] == 0xab)
							tcData[lnI] = '<';	// Convert back to < character
						if (tcData[lnI] == 0xbb)
							tcData[lnI] = '>';	// Convert back to > character
					}


				if (tcOut && *tcOut)
				{
					memcpy(*tcOut + tnFileLength,								tcOpenCharacters,	strlen(tcOpenCharacters));
					memcpy(*tcOut + tnFileLength + strlen(tcOpenCharacters),	tcData,				tnLength);
				}
				tnFileLength += (s32)strlen(tcOpenCharacters);
				tnFileLength += tnLength;


				// Write any attributes
				save__write_attribute(tfh, tcOut, a, tnFileLength);


				// Close the tag
				if (tfh)
				{
					numread3 = _write(tfh, tcCloseCharacters, (u32)strlen(tcCloseCharacters));
					if (numread3 != (u32)strlen(tcCloseCharacters))
					{
						// Some error writing
						return(false);
					}
				}
				if (tcOut && *tcOut)
					memcpy(*tcOut + tnFileLength, tcCloseCharacters, strlen(tcCloseCharacters));

				tnFileLength += (s32)strlen(tcCloseCharacters);

				// We're good
				return(true);
			}
			// Nothing to write
			return(true);
		}


		bool save__write_attribute(int tfh, s8** tcOut, CXml* a, s32& tnFileLength)
		{
			u32 numread1, numread2, numread3, numread4, numread5;
			u32 length1,  length2,  length3,  length4,  length5;


			// Write any attributes
			while (a)
			{
				if (a->tag())
				{
					// There is a tag here
					if (a->data())
					{
						// And data, we're good to go
						length1 = 1;
						length2 = a->tag()->length();
						length3 = 2;
						length4 = a->data()->length();
						length5 = 1;
						if (tfh)
						{
							numread1 = _write(tfh, " ",							length1);
							numread2 = _write(tfh, a->tag()->as_s8p(),	length2);
							numread3 = _write(tfh, "='",						length3);
							numread4 = _write(tfh, a->data()->as_s8p(),	length4);
							numread5 = _write(tfh, "'",							length5);
							if (numread1 != length1 || numread2 != length2 || numread3 != length3 || numread4 != length4 || numread5 != length5)
							{
								// Some error writing
								return(false);
							}
							// We're good, tag is written
						}
						if (tcOut && *tcOut)
						{
							memcpy(*tcOut + tnFileLength,											" ",						length1);
							memcpy(*tcOut + tnFileLength + length1,									a->tag()->as_s8p(),	length2);
							memcpy(*tcOut + tnFileLength + length1 + length2,						"='",						length3);
							memcpy(*tcOut + tnFileLength + length1 + length2 + length3,				a->data()->as_s8p(),	length4);
							memcpy(*tcOut + tnFileLength + length1 + length2 + length3 + length4,	"'",						length5);

						}
						tnFileLength += length1;
						tnFileLength += length2;
						tnFileLength += length3;
						tnFileLength += length4;
						tnFileLength += length5;
					}
				}

				// Move to next attribute
				a = a->attribute();
			}
			// No error
			return(true);
		}



	private:
		CXml*			m_next;			// Pointer to next item in two-way linked list
		CXml*			m_prev;			// Pointer to previous item in two-way linked list
		CXml*			m_parent;		// Pointer to parent XMLTag

		CXml*			m_child;		// First child
		CXml*			m_attribute;	// First attribute

		XmlData*		m_tag;			// Holds data item for tag name, data and length
		XmlData*		m_data;			// Holds data item for the tag contents, such as the data between <this> and </this>
		XmlData*		m_cdata;		// Holds a CDATA item

		bool			m_closed;		// Indicates whether or not this node has been properly closed.  For a well-formed XML document, all nodes will be closed properly
	};

	typedef CXml* CXmlp;
