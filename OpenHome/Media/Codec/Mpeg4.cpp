#include <Linn/Media/Codec/Mpeg4.h>

#include <string.h>

using namespace OpenHome;
using namespace OpenHome::Media;
using namespace OpenHome::Media::Codec;

// Mpeg4Box

Mpeg4Box::Mpeg4Box(Selector& aSelector, TUint32 aOffset, TUint32 aBoxSize, const TChar* aIdName)
    : iSelector(aSelector)
    , iOffset(aOffset)
    , iDataBytes(0)
    , iBytesRead(0)
    , iBoxBytesRead(0)
    , iBoxSize(aBoxSize)
{
    if(aIdName != NULL)
        FindBox(aIdName);
}


Mpeg4Box::~Mpeg4Box()
{
}

TBool Mpeg4Box::FindBox(const TChar* aIdName)
{
    while(!Empty()) {
        ExtractHeaderId();
        if(Match(aIdName)) {
            return true;              // found required id
        }
        SkipEntry();                  // skip over this entry
    }

    return false;
}

TBool Mpeg4Box::Empty()
{ 
    if (iBoxSize > BytesRead()+8) {
        return false;
    }
    return true;
}

void Mpeg4Box::ExtractHeaderId()
{
    iBytesRead = 0;

    Bws<4> databytes;
    Read(databytes, 4);
    iDataBytes = databytes.BeUint32At(0);
    Read(iId, 4);

    LOG(kCodec, "Mpeg4 header %d (", iDataBytes);
    LOG(kCodec, iId);
    LOG(kCodec, ")\n");
}

void Mpeg4Box::Read(Bwx& aData, TUint aBytes)
{
  	aData.SetBytes(0);
    iSelector.Peek(aData, iOffset + iBoxBytesRead + iBytesRead, aBytes);
    iBytesRead += aBytes;
/*  TUint8* data = (TUint8*)aData.Ptr();
    LOG(kCodec, "Box Read %d bytes [%x][%x][%x][%x][%x][%x][%x][%x]\n", aBytes, 
                data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]); */
}

void Mpeg4Box::SkipEntry()
{
    LOG(kCodec, " SkipEntry %d, %d\n", iDataBytes, iBytesRead);
    iBytesRead += (iDataBytes - iBytesRead);
    iBoxBytesRead += iBytesRead;
    iBytesRead = 0;
}

void Mpeg4Box::Skip(TUint32 aBytes)
{
    iBytesRead += aBytes;
}

void Mpeg4Box::AddBytesRead(TUint32 aBytes)
{
    iBytesRead += aBytes;
    LOG(kCodec, " AddBytesRead %d, %d\n", aBytes, iBytesRead);
}

TBool Mpeg4Box::Match(const TChar* aIdName)
{
    if(iId != Brn(aIdName)) {
        return false;   
    }
    LOG(kCodec, " Match \"%s\" {", aIdName);
    LOG(kCodec, iId);
    LOG(kCodec, "}\n");
    return true;
}


// Mpeg4

Mpeg4::Mpeg4(Selector& aSelector)
    : iContainerSize(0)
{
    LOG(kCodec, "Mpeg4::Mpeg4 checking for Mpeg4 header\n");
    
    Bws<100> data;
    aSelector.Peek(data, 4, 4);
    if(data != Brn("ftyp")) {
        LOG(kCodec, " no ftyp found at start of file\n");
        THROW(MediaMpeg4FileInvalid);
    }

    // data could be stored in different orders in the file but ftyp & moov must come before mdat
    // This loop terminates when:
    // - we find the start of data
    // - Selector throws an exception (eos, flush)

	Mpeg4Box BoxL1(aSelector, 0, aSelector.BytesTotal());
	while(1) {                              // keep on reading until start of data found
		BoxL1.ExtractHeaderId();            // get next header
		if(BoxL1.Match("mdat")) {
			LOG(kCodec, "Mpeg4 data found\n");
			iContainerSize = BoxL1.TotalOffset(); //set true header size
							  // some files contain extra text at start of the data section which needs to be skipped
			BoxL1.Read(data, 16);
			TByte* datap = (TUint8*)data.Ptr();
			if((datap[3] == 0x08) && (Brn(&datap[4], 4) == Brn("wide")) && (Brn(&datap[12], 4) == Brn("mdat"))) {
				LOG(kCodec, "extra mdat info found - skip\n");
				iContainerSize += 16;
			}
			return;
		} else if(BoxL1.Match("wide")) {
			// no data of interest - sometimes inserted by quicktime before 'mdat'
		} else if(BoxL1.Match("ftyp")) {
			// no data of interest
		} else if(BoxL1.Match("moov")) {
			LOG(kCodec, "Mpeg4 moov found\n");
			// now search through levels for stsd for audio info

			Mpeg4Box BoxL2(aSelector, BoxL1.TotalOffset(), BoxL1.DataBytes(), "trak");
			Mpeg4Box BoxL3(aSelector, BoxL2.TotalOffset(), BoxL2.DataBytes(), "mdia");
			Mpeg4Box BoxL4(aSelector, BoxL3.TotalOffset(), BoxL3.DataBytes());
			while(!BoxL4.Empty()) {                           // while box L3 size > box L4 read bytes
				BoxL4.ExtractHeaderId();              // get next header
				if(BoxL4.Match("mdhd")) {
					BoxL4.Read(data, 4);
					if(data.BeUint32At(0)) {
						// read as 64 bit values  - ToDo !!!!
						THROW(MediaMpeg4FileInvalid);
					}
					else {
						BoxL4.Skip(8);
						BoxL4.Read(data, 4);
						aSelector.iCodecContainer->SetTimescale(data.BeUint32At(0));
						BoxL4.Read(data, 4);
						aSelector.iCodecContainer->SetDuration(data.BeUint32At(0));
					}
				} else if(BoxL4.Match("minf")) {
					Mpeg4Box BoxL5(aSelector, BoxL4.TotalOffset(), BoxL4.DataBytes(), "stbl");
					Mpeg4Box BoxL6(aSelector, BoxL5.TotalOffset(), BoxL5.DataBytes());
					while(!BoxL6.Empty()) {
						BoxL6.ExtractHeaderId();

						if(BoxL6.Match("stsd")) {
							BoxL6.Skip(12);
							BoxL6.Read(data, 4);
							aSelector.iCodecContainer->SetName(data.Split(0,4));      // extract codec name

							LOG(kCodec, " Mpeg4 codec Name [");
							LOG(kCodec, aSelector.iCodecContainer->Name());
							LOG(kCodec, "]\n");

							BoxL6.Skip(16);
							BoxL6.Read(data, 2);
							aSelector.iCodecContainer->SetChannels(data.BeUint16At(0));
							BoxL6.Read(data, 2);
							aSelector.iCodecContainer->SetBitDepth(data.BeUint16At(0));
							BoxL6.Skip(4);
							BoxL6.Read(data, 2);
							aSelector.iCodecContainer->SetSampleRate(data.BeUint16At(0));
							BoxL6.Skip(2);              // LSB's of sample rate are ignored

							if(!BoxL6.Empty()) {
								Mpeg4Box BoxL7(aSelector, BoxL6.TotalOffset(), BoxL6.DataBytes());         // any codec specific info should follow immediately
								BoxL7.ExtractHeaderId();
								if(BoxL7.Match("alac")) {
									// extract alac specific info
									BoxL7.Read(data, BoxL7.DataBytes() - 8);
									aSelector.iCodecContainer->SetCodecSpecificData(data);
								}
								else if(BoxL7.Match("esds")) {
									// extract aac specific info
									LOG(kCodec, " esds size = 0x%x\n", BoxL7.DataBytes());
									BoxL7.Read(data, BoxL7.DataBytes() - 8);
									aSelector.iCodecContainer->SetCodecSpecificData(data);
								}

								BoxL6.AddBytesRead(BoxL7.BytesRead());
							}

						} else if(BoxL6.Match("stts")) {        // table of audio samples per sample - used to convert audio samples to codec samples
							BoxL6.Read(data, 4);                // skip version id
							BoxL6.Read(data, 4);                // extract number of entries
							TUint entries = data.BeUint32At(0);
							aSelector.iCodecContainer->iSeekTable.InitialiseAudioSamplesPerSample(entries);
							while(entries--) {
								BoxL6.Read(data, 8);
								aSelector.iCodecContainer->iSeekTable.SetAudioSamplesPerSample(data.BeUint32At(0), data.BeUint32At(4));
							}
						} else if(BoxL6.Match("stsc")) {             // table of samples per chunk - used to seek to specific sample
							BoxL6.Read(data, 4);                // skip version id
							BoxL6.Read(data, 4);                // extract number of entries
							TUint entries = data.BeUint32At(0);
							aSelector.iCodecContainer->iSeekTable.InitialiseSamplesPerChunk(entries);
							while(entries--) {
								BoxL6.Read(data, 12);
								aSelector.iCodecContainer->iSeekTable.SetSamplesPerChunk(data.BeUint32At(0), data.BeUint32At(4));
							}
						} else if(BoxL6.Match("stco")) {             // table of file offsets for each chunk   (repeat for 'co64' using 64bit offsets)

							BoxL6.Read(data, 4);                // skip version id
							BoxL6.Read(data, 4);                // extract number of entries
							TUint entries = data.BeUint32At(0);

							aSelector.iCodecContainer->iSeekTable.InitialiseOffsets(entries);
							for(TUint i = 0; i < entries; i++) {
								BoxL6.Read(data, 4);
								aSelector.iCodecContainer->iSeekTable.SetOffset((TUint64)data.BeUint32At(0));
							}
						} else if(BoxL6.Match("stsz")) {             // size of each input sample

								BoxL6.Read(data, 4);                // skip version id
								BoxL6.Read(data, 4);                // default sample size expected to be 0 - else a table won't exist
								if(data.BeUint32At(0) != 0) {
									THROW(MediaMpeg4FileInvalid);
								}

								BoxL6.Read(data, 4);
								TUint entries = data.BeUint32At(0);
								TUint samplesize;

										// allocate table for sample size entries, needed by alac decoder - remember to delete when finished - ToDo !!!
								aSelector.iCodecContainer->iSampleSizeTable.Initialise(entries);

								Bwx* samplesizetable = new Bwd(entries*4);
								BoxL6.Read(*samplesizetable, entries*4);
								for(TUint i = 0; i < entries; i++) {
									samplesize = samplesizetable->BeUint32At(i*4);
									aSelector.iCodecContainer->iSampleSizeTable.SetSampleSize(samplesize);
								}
								delete samplesizetable;
						}
						BoxL6.SkipEntry();
					}
							// update accumulated bytes read for each level
							//  - we are just interested in total but this makes it
							//    cleaner for future data extractions
					BoxL5.AddBytesRead(BoxL6.BytesRead());
					BoxL4.AddBytesRead(BoxL5.BytesRead());
				}
				BoxL4.SkipEntry();                    // skip to next entry
			}
			BoxL3.AddBytesRead(BoxL4.BytesRead());
			BoxL2.AddBytesRead(BoxL3.BytesRead());
			BoxL1.AddBytesRead(BoxL2.BytesRead());
		} else if(BoxL1.Match("pdin")) {
		    // ignore this one
		} else if(BoxL1.Match("moof")) {
			// ignore this one
		} else if(BoxL1.Match("mfra")) {
	        // ignore this one
		} else if(BoxL1.Match("free")) {
		    // ignore this one
		} else if(BoxL1.Match("skip")) {
			// ignore this one
		} else if(BoxL1.Match("meta")) {
			// ignore this one
		} else {
			LOG(kCodec, "Mpeg4 Invalid File\n");
			THROW(MediaMpeg4FileInvalid);
		}
		BoxL1.SkipEntry(); // skip to next entry
	}
}

Mpeg4::~Mpeg4()
{
    LOG(kCodec, "Mpeg4::~Mpeg4\n");
}

TUint32 Mpeg4::ContainerSize() const
{
    return iContainerSize;
}
