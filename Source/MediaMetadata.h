#pragma once
#include <pch.h>
#include "KeyStringValuePair.h"

namespace FFmpegInteropX
{
	using namespace Platform;
	using namespace Platform::Collections;
	using namespace Windows::Foundation;
	using namespace Windows::Foundation::Collections;

	class MediaMetadata
	{
		Vector<IKeyValuePair<String^, String^>^>^ entries;
		bool tagsLoaded = false;
	public:

		MediaMetadata()
		{
			entries = ref new Vector<IKeyValuePair<String^, String^>^>();
		}

		void LoadMetadataTags(AVFormatContext* m_pAvFormatCtx)
		{
			if (!tagsLoaded)
			{
				if (m_pAvFormatCtx->metadata)
				{
					AVDictionaryEntry* entry = NULL;

					do {
						entry = av_dict_get(m_pAvFormatCtx->metadata, "", entry, AV_DICT_IGNORE_SUFFIX);
						if (entry)
							entries->Append(ref new KeyStringValuePair(
								StringUtils::Utf8ToPlatformString(entry->key),
								StringUtils::Utf8ToPlatformString(entry->value)));

					} while (entry);
				}
				tagsLoaded = true;
			}
		}


		IVectorView<IKeyValuePair<String^, String^>^>^ MetadataTags()
		{
			return entries->GetView();
		}
	};
}


