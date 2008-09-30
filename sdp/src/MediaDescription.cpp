/*****************************************************************************
//	SDP Parser Classes
//
//	Media Description Class
//
//	revision of last commit:
//		$Rev$
//	author of last commit:
//		$Author$
//	date of last commit:
//		$Date$
//
//	created by Argenet {argenet@sibears.org}
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
******************************************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Includes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include "FieldFactory.h"
#include "MediaDescription.h"

using std::string;

namespace SDP {

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	MediaDescription class implementation
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	Public methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField)
	: _mediaField(mediaField)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField, const InfoField & title)
	: _mediaField(mediaField)
	, _title(title)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField,
									 const InfoField & title,
									 const ConnectionField & connectionInfo)
	: _mediaField(mediaField)
	, _title(title)
	, _connectionInfo(connectionInfo)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField,
									 const InfoField & title,
									 const ConnectionField & connectionInfo,
									 const BandwidthField & bandwidth)
	: _mediaField(mediaField)
	, _title(title)
	, _connectionInfo(connectionInfo)
	, _bandwidth(bandwidth)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField,
									 const InfoField & title,
									 const ConnectionField & connectionInfo,
									 const BandwidthField & bandwidth,
									 const KeyField & encryption)
	: _mediaField(mediaField)
	, _title(title)
	, _connectionInfo(connectionInfo)
	, _bandwidth(bandwidth)
	, _encryptionKey(encryption)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaField & mediaField,
									 const InfoField & title,
									 const ConnectionField & connectionInfo,
									 const BandwidthField & bandwidth,
									 const KeyField & encryption,
									 const AttributeVec & attributes)
	: _mediaField(mediaField)
	, _title(title)
	, _connectionInfo(connectionInfo)
	, _bandwidth(bandwidth)
	, _encryptionKey(encryption)
	, _attributes(attributes)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const std::string & mediaDescription)
{
	StringVec lines = split(mediaDescription, "\r\n");

	for(StringVec::iterator iter = lines.begin() ;
		lines.end() != iter ; 
		++iter)
	{
		if(iter->size() > 0)
		{
			Field * pField = FieldFactory::CreateInstance(*iter);
			switch((*iter)[0])
			{
				case 'm':
					_mediaField = * dynamic_cast<MediaField *>(pField);

					break;
				case 'i':
					_title = * dynamic_cast<InfoField *>(pField);

					break;
				case 'c':
					_connectionInfo = * dynamic_cast<ConnectionField *>(pField);

					break;
				case 'b':
					_bandwidth = * dynamic_cast<BandwidthField *>(pField);

					break;
				case 'k':
					_encryptionKey = * dynamic_cast<KeyField *>(pField);

					break;
				case 'a':
					_attributes.push_back(* dynamic_cast<AttributeField *>(pField));

					break;
			}

			FieldFactory::DestroyInstance(pField);
		}
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription :: MediaDescription(const MediaDescription & mediaDescription)
	: _mediaField(mediaDescription._mediaField)
	, _title(mediaDescription._title)
	, _connectionInfo(mediaDescription._connectionInfo)
	, _bandwidth(mediaDescription._bandwidth)
	, _encryptionKey(mediaDescription._encryptionKey)
	, _attributes(mediaDescription._attributes)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

MediaDescription & MediaDescription :: operator=(const MediaDescription & mediaDescription)
{
	if(&mediaDescription != this)
	{
		_mediaField = mediaDescription._mediaField;
		_title = mediaDescription._title;
		_connectionInfo = mediaDescription._connectionInfo;
		_bandwidth = mediaDescription._bandwidth;
		_encryptionKey= mediaDescription._encryptionKey;
		_attributes = mediaDescription._attributes;
	}

	return *this;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline MediaField MediaDescription :: getMediaField() const
{
	return _mediaField;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline InfoField MediaDescription :: getTitle() const
{
	return _title;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void MediaDescription :: setTitle(const InfoField & title)
{
	_title = title;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline ConnectionField MediaDescription :: getConnectionInfo() const
{
	return _connectionInfo;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void MediaDescription :: setConnectionInfo(const ConnectionField & connectionInfo)
{
	_connectionInfo = connectionInfo;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline BandwidthField MediaDescription :: getBandwidth() const
{
	return _bandwidth;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void MediaDescription :: setBandwidth(const BandwidthField & bandwidth)
{
	_bandwidth = bandwidth;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline KeyField MediaDescription :: getEncryptionKey() const
{
	return _encryptionKey;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MediaDescription :: setEncryptionKey(const KeyField & encryptionKey)
{
	_encryptionKey = encryptionKey;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline AttributeVec MediaDescription :: getAttributes() const
{
	return _attributes;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

inline void MediaDescription :: setAttributes(const AttributeVec & attributes)
{
	_attributes = attributes;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

string MediaDescription :: toString() const
{
	string str = _mediaField.toString();
	str += _title.toString();
	str += _connectionInfo.toString();
	str += _bandwidth.toString();
	str += _encryptionKey.toString();

	for(AttributeVec::const_iterator iter = _attributes.begin() ; 
		_attributes.end() != iter ; 
		++iter)
	{
		str += iter->toString();
	}

	return str;
}

} //	namespace SDP