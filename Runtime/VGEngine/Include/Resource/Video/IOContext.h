#pragma once

extern "C" {
#include <libavformat/avio.h>
#include <libavutil/error.h>
}

#include "../../Core/VFS.h"

namespace VisionGal {

    // 自定义 opaque 结构（传递 VFS 文件对象）
    struct VFS_VIDEO_IO_Context {
        vfspp::IFilePtr file; // VFSpp 文件句柄
		std::vector<uint8_t*> buffers;

		~VFS_VIDEO_IO_Context();
    };
	 
    int static_ffmpeg_read_packet(void* opaque, uint8_t* buf, int buf_size);

    int64_t static_ffmpeg_seek(void* opaque, int64_t offset, int whence);
}
