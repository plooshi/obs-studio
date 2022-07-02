#pragma once

#include <Windows.h>
#include "mfxstructures.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct qsv_rate_control_info {
	const char *name;
	bool haswell_or_greater;
};

static const struct qsv_rate_control_info qsv_ratecontrols[] = {
	{"CBR", false},   {"VBR", false}, {"VCM", true},    {"CQP", false},
	{"AVBR", false},  {"ICQ", true},  {"LA_ICQ", true}, {"LA_CBR", true},
	{"LA_VBR", true}, {0, false}};
static const char *const qsv_profile_names[] = {"Main", "Main 10", 0};
static const char *const qsv_usage_names[] = {"quality",  "balanced", "speed",
					      "veryslow", "slower",   "slow",
					      "medium",   "fast",     "faster",
					      "veryfast", 0};
static const char *const qsv_latency_names[] = {"ultra-low", "low", "normal",
						0};
typedef struct qsv_t qsv_t;

typedef struct {
	mfxU16 nTargetUsage; /* 1 through 7, 1 being best quality and 7
				being the best speed */
	mfxU16 nWidth;       /* source picture width */
	mfxU16 nHeight;      /* source picture height */
	mfxU16 nAsyncDepth;
	mfxU16 nFpsNum;
	mfxU16 nFpsDen;
	mfxU16 nTargetBitRate;
	mfxU16 nMaxBitRate;
	mfxU16 nCodecProfile;
	mfxU16 nRateControl;
	mfxU16 nAccuracy;
	mfxU16 nConvergence;
	mfxU16 nQPI;
	mfxU16 nQPP;
	mfxU16 nQPB;
	mfxU16 nLADEPTH;
	mfxU16 nKeyIntSec;
	mfxU16 nbFrames;
	mfxU16 nICQQuality;
	bool bMBBRC;
	bool bCQM;
	bool bHLG;
} qsv_param_t;

enum qsv_cpu_platform {
	QSV_CPU_PLATFORM_UNKNOWN,
	QSV_CPU_PLATFORM_BNL,
	QSV_CPU_PLATFORM_SNB,
	QSV_CPU_PLATFORM_IVB,
	QSV_CPU_PLATFORM_SLM,
	QSV_CPU_PLATFORM_CHT,
	QSV_CPU_PLATFORM_HSW,
	QSV_CPU_PLATFORM_BDW,
	QSV_CPU_PLATFORM_SKL,
	QSV_CPU_PLATFORM_APL,
	QSV_CPU_PLATFORM_KBL,
	QSV_CPU_PLATFORM_GLK,
	QSV_CPU_PLATFORM_CNL,
	QSV_CPU_PLATFORM_ICL,
	QSV_CPU_PLATFORM_INTEL
};

int qsv_hevc_encoder_close(qsv_t *);
int qsv_hevc_encoder_reconfig(qsv_t *, qsv_param_t *);
void qsv_hevc_encoder_version(unsigned short *major, unsigned short *minor);
qsv_t *qsv_hevc_encoder_open(qsv_param_t *);
int qsv_hevc_encoder_encode(qsv_t *, uint64_t, uint8_t *, uint8_t *, uint32_t,
			    uint32_t, mfxBitstream **pBS);
int qsv_hevc_encoder_encode_tex(qsv_t *, uint64_t, uint32_t, uint64_t,
				uint64_t *, mfxBitstream **pBS);
int qsv_hevc_encoder_headers(qsv_t *pContext, uint8_t **pVPS, uint8_t **pSPS,
			     uint8_t **pPPS, uint16_t *pnVPS, uint16_t *pnSPS,
			     uint16_t *pnPPS);
enum qsv_cpu_platform qsv_get_cpu_platform(); // in the QSV_Encoder.cpp
bool prefer_igpu_hevc_enc(int *iGPUIndex);

#ifdef __cplusplus
}
#endif
