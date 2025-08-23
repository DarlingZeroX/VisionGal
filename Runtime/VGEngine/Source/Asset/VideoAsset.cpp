#include "Asset/VideoAsset.h"

namespace VisionGal
{
	// �Զ��� opaque �ṹ������ VFS �ļ�����
	//struct VFSIOContext {
	//	vfspp::IFilePtr file; // VFSpp �ļ����
	//};
	//
	//static int read_packet(void* opaque, uint8_t* buf, int buf_size) {
	//	VFSIOContext* ctx = static_cast<VFSIOContext*>(opaque);
	//	// ���� VFSpp �� Read �ӿ�
	//	uint64_t bytes_read = ctx->file->Read(buf, static_cast<uint64_t>(buf_size));
	//	if (bytes_read == 0) return AVERROR_EOF; // �ļ�����
	//	return static_cast<int>(bytes_read);
	//}

	bool VideoAssetLoader::Read(const std::string path, Ref<VGAsset>& asset)
	{
		auto videoAsset = CreateRef<VideoAsset>();
		videoAsset->videoClip = CreateRef<VideoClip>();
		videoAsset->videoClip->decoder = CreateRef<VideoDecoder>();

		if ( videoAsset->videoClip->decoder->Open(path))
		{
			asset = videoAsset;
			return true;
		}

		return false;
		/*
		auto& vfs = Core::GetVFS();

		// ���Դ��ļ�
		auto file = vfs->OpenFile(vfspp::FileInfo(path), vfspp::IFile::FileMode::Read);
		if (!file)
			return false;

		// �ļ��Ƿ��
		if (file->IsOpened() == false)
			return false;

		// ��ffmpeg��ȡ��Ƶ
		//AVFormatContext* fmt_ctx = avformat_alloc_context();
		videoAsset->videoClip->pFormatCtx = avformat_alloc_context();
		VFSIOContext io_ctx{ file }; // file ���Ѵ򿪵� vfspp::IFile ����

		// ���� AVIOContext���ؼ�����
		const int buffer_size = 4096; // ���黺������С
		unsigned char* io_buffer = static_cast<unsigned char*>(av_malloc(buffer_size));
		AVIOContext* avio_ctx = avio_alloc_context(
			io_buffer, buffer_size,       // ����������С
			0,                            // ֻ��ģʽ
			&io_ctx,                      // ���ݸ��ص��� opaque ����
			read_packet,                  // �󶨻ص�����
			nullptr,                      // ����д�ص�
			nullptr                        // Seek �ص�����ѡ��
		);

		// ������ FormatContext
		videoAsset->videoClip->pFormatCtx->pb = avio_ctx;

		// ����Ƶ�ļ� ע�⣺�ļ����� nullptr��������Դ�����Զ��� I/O
		int ret = avformat_open_input(&videoAsset->videoClip->pFormatCtx, nullptr, nullptr, nullptr);
		if (ret < 0) {	// Couldn't open file
			char err_buf[256];
			av_strerror(ret, err_buf, sizeof(err_buf));
			// ������������׳��쳣
			return false;
		}

		// ��ȡ����Ϣ
		if (avformat_find_stream_info(videoAsset->videoClip->pFormatCtx, nullptr) < 0)
			return false; // Couldn't find stream information

		// ��Ƶ�ļ��Ķ�����в�����Ƶ��
		videoAsset->videoClip->videoStream = -1;

		for (int i = 0; i < videoAsset->videoClip->pFormatCtx->nb_streams; i++) {
			if (videoAsset->videoClip->pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
				videoAsset->videoClip->videoStream = i;
				break;
			}
		}

		if (videoAsset->videoClip->videoStream == -1)
			return false; // Didn't find a video stream

		// videoAsset->pFormatCtx->streams�������������飬videoAsset->videoStreamָ����Ҫ��ȡ����Ƶ��������codecpar���Ǹ���Ƶ���ı���������
		AVCodecParameters* pVideoParams = videoAsset->videoClip->pFormatCtx->streams[videoAsset->videoClip->videoStream]->codecpar;

		// ʹ��avcodec_find_decoder���������ݻ�ȡ�ı��������е�codec_id��������� ID������ϵͳ�в��Ҷ�Ӧ�Ľ�����������ֵ����codec��
		const AVCodec* codec = avcodec_find_decoder(pVideoParams->codec_id);

		if (codec == nullptr)
			return false; // Codec not found

		// ʹ��avcodec_alloc_context3������Ϊ�ҵ��Ľ���������һ������������ģ������丳��videoAsset��pCodecCtx��Ա��
		videoAsset->videoClip->pCodecCtx = avcodec_alloc_context3(codec);

		// �ѵ�һ����ȡ�ı�������pVideoParams�е���Ϣ��䵽�ոշ���ı����������videoAsset->pCodecCtx�С���������������ľ;߱�����ȷ������Ƶ������Ĳ�����
		avcodec_parameters_to_context(videoAsset->videoClip->pCodecCtx, pVideoParams);

		if (avcodec_open2(videoAsset->videoClip->pCodecCtx, NULL, NULL) < 0)
			return false;

		// �����ڴ����ڴ洢ͼ������
		videoAsset->videoClip->pFrame = av_frame_alloc();
		videoAsset->videoClip->pFrameRGB = av_frame_alloc();


		videoAsset->videoClip->buffer = (uint8_t*)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_RGB24, videoAsset->videoClip->pCodecCtx->width, videoAsset->videoClip->pCodecCtx->height, 0));
		av_image_fill_arrays(videoAsset->videoClip->pFrameRGB->data, &videoAsset->videoClip->pFrameRGB->linesize[0], videoAsset->videoClip->buffer, AV_PIX_FMT_RGB24, videoAsset->videoClip->pCodecCtx->width, videoAsset->videoClip->pCodecCtx->height, 1);
		*/
		return true;
	}
}
