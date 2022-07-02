#pragma once
#include "mfxastructures.h"
#include "mfxvideo++.h"
#include "QSV_HevcEncoder.h"
#include "common_utils.h"

class QSV_HevcEncoder_Internal {
public:
	QSV_HevcEncoder_Internal(mfxIMPL &impl, mfxVersion &version);
	~QSV_HevcEncoder_Internal();

	mfxStatus Open(qsv_param_t *pParams);
	void GetVpsSpsPps(mfxU8 **pVPSBuf, mfxU8 **pSPSBuf, mfxU8 **pPPSBuf,
			  mfxU16 *pnVPSBuf, mfxU16 *pnSPSBuf, mfxU16 *pnPPSBuf);
	mfxStatus Encode(uint64_t ts, uint8_t *pDataY, uint8_t *pDataUV,
			 uint32_t strideY, uint32_t strideUV,
			 mfxBitstream **pBS);
	mfxStatus Encode_tex(uint64_t ts, uint32_t tex_handle,
			     uint64_t lock_key, uint64_t *next_key,
			     mfxBitstream **pBS);
	mfxStatus ClearData();
	mfxStatus Reset(qsv_param_t *pParams);

protected:
	mfxStatus InitParams(qsv_param_t *pParams);
	mfxStatus AllocateSurfaces();
	mfxStatus GetVideoParam();
	mfxStatus InitBitstream();
	mfxStatus LoadNV12(mfxFrameSurface1 *pSurface, uint8_t *pDataY,
			   uint8_t *pDataUV, uint32_t strideY,
			   uint32_t strideUV);
	mfxStatus LoadP010(mfxFrameSurface1 *pSurface, uint8_t *pDataY,
			   uint8_t *pDataUV, uint32_t strideY,
			   uint32_t strideUV);

	mfxStatus Drain();
	int GetFreeTaskIndex(Task *pTaskPool, mfxU16 nPoolSize);

private:
	mfxIMPL m_impl;
	mfxVersion m_ver;
	MFXVideoSession m_session;
	mfxFrameAllocator m_mfxAllocator;
	mfxVideoParam m_mfxEncParams;
	mfxFrameAllocResponse m_mfxResponse;
	mfxFrameSurface1 **m_pmfxSurfaces;
	mfxU16 m_nSurfNum;
	MFXVideoENCODE *m_pmfxENC;

	static const mfxU16 kVPSBufferCapacity{1024};
	static const mfxU16 kSPSBufferCapacity{1024};
	static const mfxU16 kPPSBufferCapacity{1024};
	mfxU8 m_VPSBuffer[kVPSBufferCapacity];
	mfxU8 m_SPSBuffer[kSPSBufferCapacity];
	mfxU8 m_PPSBuffer[kPPSBufferCapacity];
	mfxU16 m_nVPSBufferSize{kVPSBufferCapacity};
	mfxU16 m_nSPSBufferSize{kSPSBufferCapacity};
	mfxU16 m_nPPSBufferSize{kPPSBufferCapacity};

	mfxVideoParam m_parameter;
	mfxExtCodingOption3 m_co3;
	mfxExtCodingOption2 m_co2;
	mfxExtCodingOption m_co;
	mfxExtHEVCParam m_ExtHEVCParam{};
	mfxExtVideoSignalInfo m_ExtVideoSignalInfo{};
	mfxU16 m_nTaskPool;
	Task *m_pTaskPool;
	int m_nTaskIdx;
	int m_nFirstSyncTask;
	mfxBitstream m_outBitstream;
	bool m_bIsWindows8OrGreater;
	bool m_bUseD3D11;
	bool m_bD3D9HACK;
	static mfxU16 g_numEncodersOpen;
	static mfxHDL
		g_DX_Handle; // we only want one handle for all instances to use;
};
