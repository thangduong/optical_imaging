Attribute VB_Name = "ifcapidecl"


Option Explicit

Global Const IFC_DEFAULT_FLAG = 0
Global Const IFC_DIB_SINK = 1
Global Const IFC_DDRAW_SINK = 2
Global Const IFC_YCRCB_SINK = 4
Global Const IFC_IMG_SINK = 8
Global Const IFC_SW_OVERLAY = &H100&
Global Const IFC_HW_OVERLAY = &H200&
Global Const IFC_LIVE_IMAGE = &H10000
Global Const IFC_STRETCH_TO_FIT = -1#

Global Const IFC_IMGSRC_OPT_PIX_LEAST_SIG = 1
Global Const IFC_IMGSRC_OPT_BAYER_GB_RG = 2

Global Const SLOT0 = 0
Global Const SLOT1 = 1
Global Const SLOT2 = 2
Global Const SLOT3 = 3
Global Const SLOT4 = 4
Global Const SLOT5 = 5
Global Const SLOT6 = 6
Global Const SLOT7 = 7
Global Const SLOT8 = 8
Global Const SLOT9 = 9
Global Const SEQ0 = 100
Global Const SEQ1 = 101
Global Const SEQ2 = 102
Global Const SEQ3 = 103
Global Const SEQ4 = 104
Global Const SEQ5 = 105
Global Const SEQ6 = 106
Global Const SEQ7 = 107
Global Const SEQ8 = 108
Global Const SEQ9 = 109


Global Const IFC_GOPT_AUTO_FRAME_LOCK = 1
Global Const IFC_GOPT_SYSCOLOR_CLIP = 2
Global Const IFC_GOPT_LEFTJUSTIFIED = 4
Global Const IFC_GOPT_FRAME_TIME_TAG = 8
Global Const IFC_GOPT_VERT_PLANAR = &H10&
Global Const IFC_GOPT_PLANAR_INIT = &H20&



' error types */
Global Const WARNING = 1                      ' low incidence error */
Global Const SEVERE = 2                       ' high incidence error */
Global Const ABORT = 3                        ' abortive condition */
Global Const MAX_ERRLVL = 3                   ' maximum error level value */

' error message display methods */
Global Const ITX_NO_EMSG = 1                  ' don't use error messages */
Global Const ITX_DISP_EMSG = 2                ' display err messages as they occur */
Global Const ITX_QUE_EMSG = 3                 ' queue error messages */
Global Const ITX_FILE_EMSG = 4                ' store errors msgs in a file */
Global Const MAX_EMSG_STATE = 4               ' maximum error msg disp state value */

' Enumeration

Enum IFC_IMGFILE_TYPE
    TIFF_IMGFILE = 1
    PCX_IMGFILE
    BMP_IMGFILE
    CUT_IMGFILE
    FLF_IMGFILE
End Enum


Enum IFC_TRANSFORM_TYPE
        IFC_NO_TRANSFORM
        IFC_FLIP_TRANSFORM              ' Top-Bottom Flip
        IFC_MIRROR_TRANSFORM
        IFC_ROT180_TRANSFORM
End Enum


' Image class type for TIFF files
Enum IFFCLASS_TYPE

    IFFCL_BILEVEL       ' 1 BPP
    IFFCL_GRAY          ' 2,4,6,8 BPP
    IFFCL_PALETTE       ' 2,4,6,8 BPP
    IFFCL_RGB           ' 24 BPP chunky
    IFFCL_RGBPLANAR     ' 24 BPP in 8 bit planes
    IFFCL_RGBA          ' 32 BPP chunky
    IFFCL_RGBAPLANAR    ' 32 BPP in four 8 bit planes
    IFFCL_CMYK
    IFFCL_YCC
    IFFCL_CIELAB
End Enum

' Image Compression type for TIFF files
Enum IFFCOMPRESSION_TYPE

    IFFCOMP_NONE ' no compression
    IFFCOMP_DEFAULT ' whatever is defined for the format
    IFFCOMP_RLE ' various RLE schemes (PACKBITS in TIFF)
    IFFCOMP_CCITT1D ' TIFF modified G3
    IFFCOMP_CCITTG3 ' TIFF raw G3
    IFFCOMP_CCITTG4 ' TIFF G4
    IFFCOMP_LZW ' Lempel-Zif
    IFFCOMP_LZWHPRED ' LZW with TIFF horizontal differencing
    IFFCOMP_JPEG ' JPEG compression
End Enum

Enum LUTID_TYPE
        INPUT_LUT1
        INPUT_LUT2
        INPUT_LUT3
        INPUT_LUT4
        OUTPUT_LUT1
        OUTPUT_LUT2
        OUTPUT_LUT3
        OUTPUT_LUT4
        IFC_NUM_LUTIDS
End Enum

Enum LUT_PORTION_TYPE
        LUT_LOW_BYTE
        LUT_HIGH_BYTE
        LUT_FULL_WORD
        LUT_INTELLI_WIDTH
End Enum

Enum IFC_LUT_PIX_SIZE_TYPE
        IFC_LUT_PIX_SIZE_8 = 8
        IFC_LUT_PIX_SIZE_10 = 10
        IFC_LUT_PIX_SIZE_12 = 12
        IFC_LUT_PIX_SIZE_14 = 14
        IFC_LUT_PIX_SIZE_16 = 16
        IFC_NUM_LUT_PIX_SIZES
End Enum

Enum IFC_POLARITY_TYPE
        IFC_ACTIVE_LOW
        IFC_ACTIVE_HIGH
End Enum

Enum IFC_LEVEL_TYPE
        IFC_LEVEL_LOW
        IFC_LEVEL_HIGH
End Enum

Enum IFC_EDGE_TYPE
        IFC_FALLING_EDGE
        IFC_RISING_EDGE
End Enum

Enum IFC_ENABLE_TYPE
        IFC_Disable
        IFC_Enable
End Enum

Enum IFC_TRIG_SRC_TYPE
        IFC_SOFT_TRIG
        IFC_EXT0_TRIG
        IFC_EXT1_TRIG
        IFC_EXT2_TRIG
        IFC_EXT3_TRIG
End Enum

Enum IFC_SYNC_TYPE
        IFC_SYNC
        IFC_ASYNC
End Enum

Enum IFC_STROBE_MODE_TYPE
        IFC_FAST_STROBE
        IFC_SLOW_STROBE
End Enum

Enum IFC_FRAME_RESET_SIZE_TYPE
        IFC_FRAME_RESET_TRUE_DURING_FRAME_OFFSET
        IFC_FRAME_RESET_TRUE_FOR_ONE_LINE
End Enum

Enum IFC_CSC_TYPE
        IFC_CSC_IGNORE
        IFC_CSC_RGB_TO_RGB
        IFC_CSC_RGB_TO_YUV
        IFC_CSC_RGB_TO_YIQ
        IFC_CSC_RGB_TO_YCRCB444
        IFC_CSC_RGB_TO_YCRCB
        IFC_CSC_RGB_TO_YCBCR422
        IFC_CSC_HSI
End Enum

' These are the parameters common to all modules. A given module
' will usually support a subset of these common parameters and
' also have some module-specific parameters.
'
Enum COMMON_PARAMS_TYPE
        P_PIXEL_SIZE = 1                ' RANGE 1..32
        P_STROBE_MODE
        P_STROBE_POLARITY
        P_STROBE_DELAY
        P_FRAME_RESET_MODE
        P_FRAME_RESET_POLARITY
        P_FRAME_RESET_OFFSET
        P_FRAME_RESET_SIZE


        P_TRIGGER_ENABLE                ' IFC_ENABLE_TYPE
        P_TRIGGER_SRC                   ' IFC_TRIG_SRC_TYPE
        P_TRIGGER_POLARITY              ' IFC_EDGE_TYPE
        P_TRIGGER_STATE         ' IFC_LEVEL_TYPE
        P_GEN_SW_TRIGGER                ' any value

        P_CONTRAST                              ' range 0..100
        P_BRIGHTNESS                    ' range 0..100
        P_CUR_ACQ_LINE


        P_LEN_ENABLE                    ' IFC_ENABLE_TYPE
        P_LEN_SYNC                              ' IFC_SYNC_TYPE
        P_LEN_POLARITY          ' IFC_EDGE_TYPE

        P_FEN_ENABLE                    ' IFC_ENABLE_TYPE
        P_FEN_POLARITY          ' IFC_EDGE_TYPE
        P_HORZ_OFF                              ' Module peculiar integer range
        P_WIDTH_PIXELS                  ' Module peculiar integer range
        P_VERT_OFF                              ' Module peculiar integer range
        P_HEIGHT_PIXELS         ' Module peculiar integer range

        P_FIRST_FIELD_STAT              ' IFC_FIELD_STATUS
        P_FIRST_FIELD_CMD               ' IFC_FIELD_STATUS
        P_SCAN_MODE_STAT                ' IFC_ILACE

        P_HSYNC_FREQ
        P_HSYNC_WIDTH
        P_HSYNC_POLARITY
        P_HSYNC_SRC
        P_HSYNC_SIGNAL_TYPE
        P_VSYNC_FREQ
        P_VSYNC_WIDTH
        P_VSYNC_POLARITY
        P_VSYNC_SRC
        P_VSYNC_SIGNAL_TYPE
        P_PIXEL_CLK_FREQ
        P_PIXEL_CLK_POLARITY
        P_PIXEL_CLK_SRC
        P_PIXEL_CLK_SIGNAL_TYPE
        P_NUM_EQ_PULSES_FPORCH
        P_NUM_EQ_PULSES_BPORCH
        P_EQ_PULSE_WIDTH
        P_SERR_PULSE_WIDTH
        P_CLAMP_MODE
        P_CLAMP_SEG
        P_CLAMP_HSYNC_EDGE
        P_CLAMP_OFFSET_TIME
        P_CLAMP_LEVEL
        P_PEDESTAL
        P_TIMING_INPUT_CHANNEL

        ' Genral Color Space Option: can affect both CSC matrix and LUTS. If
        ' this parameter is applicable P_COLOR_SPACE_CONV_COEFFS is
        ' ignored.
        P_COLOR_SPACE_CONV

        ' Coefficients for linear color space conversion matrix. For most
        ' hardware modules this is subordinate to P_COLOR_SPACE_CONV. I.e.
        ' if P_COLOR_SPACE_CONV is applicable then this is ignored.
        P_COLOR_SPACE_CONV_COEFFS

        ' Identifies the set of parameter groups applicable for a given camera definition
        P_PARAM_GROUPS_APPLICABLE
        P_PIXEL_COLOR
        P_ANALOG_GAIN
        P_APPLICABLE_CAM_PORT
        P_STROBE_ENABLE

        P_INPUT_LUT1_FILE
        P_INPUT_LUT2_FILE
        P_INPUT_LUT3_FILE
        P_INPUT_LUT4_FILE

        P_FIELD_SRC
        P_FIELD_SHIFT
        P_CAM_MODEL_NAME
        P_COM_PORT_NAME
        P_COM_PORT_BYTESIZE
        P_COM_PORT_BAUDRATE
        P_COM_PORT_PARITY
        P_COM_PORT_STOPBITS
        P_VIDEO_STANDARD
        P_BAYER_FILTER
        P_SATURATION
        P_HUE
        P_BAYER_GAIN_RED
        P_BAYER_GAIN_GREEN
        P_BAYER_GAIN_BLUE
        P_FRAME_RESET_GATE
        P_FRAMES_PER_TRIGGER
        P_STROBE_DURATION
        P_TRIGGER_DEBOUNCE

    ' Add new types above as needed

        GEN_PARAM_END_MARKER    ' Always keep these three last.
    IFC_LAST_SUP_PARAM = -1
    PARAM_NOT_SUPPORTED = 0
End Enum


Enum IFC_PARAM_KIND
    IFC_ENUM_TYPE
    IFC_INTEGER_TYPE
    IFC_Single_TYPE
    IFC_STRING_TYPE
    IFC_POINTER_TYPE
    IFC_Single_SET_TYPE
    IFC_INT_SET_TYPE
End Enum

Enum IFC_PARAM_GROUP_TYPE
        IFC_PGRP_CAM_TIMING_INPUT = 1 ' Parameters pertaining to camera timing inputs
        IFC_PGRP_CAM_TIMING_OUTPUT ' Parameters pertaining to camera timing outputs
        IFC_PGRP_MULTI_CAMERA           ' Parameters pertaining to multiple cameras on one board
        IFC_PGRP_GENERAL_ACQ            ' General acquisition parameters e.g. window generator pixel depth ...
        IFC_PGRP_TRIGGER                        ' Trigger related parameters
        IFC_PGRP_CUSTOM_CAMERA          ' Advanced custom camera definition parameters e.g. special EXO files

        IFC_PGRP_NUM_GROUPS
    IFC_LAST_SUPPORT_PGRP = -1
    IFC_GROUP_NOT_SUPPORTED = 0

End Enum

' Interrupt Events supported by Image Capture Modules
Enum ICAP_INTR_EVENT
        ICAP_INTR_VB      '/* vertical blank */
        ICAP_INTR_ODD_VB
        ICAP_INTR_EVEN_VB
        ICAP_INTR_AM
        ICAP_INTR_TRIG
        ICAP_INTR_ACQ_ADRS
        ICAP_INTR_ACQ
        ICAP_INTR_BMDONE
        ICAP_INTR_INPORT
        ICAP_INTR_END_TRIG
        ICAP_INTR_SOACQ
        ICAP_INTR_EOF

        ICAP_INTR_MAX_EVENT  '/* MUST be last !!! */
End Enum


Enum PCD_TRIG_SRC_TYPE
        PCD_DIFFERENTIAL_TRIG
        PCD_TTL_TRIG
        PCD_OPTO_COUPLED_TRIG
End Enum

Enum PCD_TRIG_MODE_TYPE
        PCD_TMODE_DISABLE = 0
        PCD_TMODE_HWTRIG0_ASSERT = 2
        PCD_TMODE_HWTRIG0_DEASSERT = 3
        PCD_TMODE_HWTRIG1_ASSERT = 4
        PCD_TMODE_HWTRIG1_DEASSERT = 5
        PCD_TMODE_SWTRIG0 = 6
        PCD_TMODE_SWTRIG1 = 7
End Enum


Enum PCD_MULTI_INPUT_TYPE
        PCD_MULTI_INPUT_FIELD
        PCD_MULTI_INPUT_VALID_DATA
End Enum

Enum PCD_EXSYNC_MODE_TYPE
        PCD_EXSYNC_FREE_RUNNING
        PCD_EXSYNC_TRIG1
        PCD_EXSYNC_TRIG2
        PCD_EXSYNC_SOFT_TRIG
        PCD_EXSYNC_VB_TRIG
End Enum


Enum PCD_IMAGE_GEOMETRY_TYPE
        PCD_1CHAN_L2R                           ' |AAA..........AA|
        PCD_2CHAN_INTERLEAVED           ' |ABABAB...AB|
        PCD_2CHAN_SEP_TAP_L2R           ' 2 CHANNELS SEPERATE TAPS LEFT TO RIGHT        |A=>            |B=>            |
        PCD_2CHAN_SEP_TAP_R2L           ' 2 CHANNELS SEPERATE TAPS RIGHT TO LEFT        |            <=A|            <=B|
        PCD_4CHAN_SEP_TAP_L2R           ' 4 CHANNELS SEPERATE TAPS LEFT TO RIGHT        |A=>    |B=>    |C=>    |D=>    |
        PCD_4CHAN_SEP_TAP_R2L           ' 4 CHANNELS SEPERATE TAPS RIGHT TO LEFT        |    <=A|    <=B|    <=C|    <=D|
        PCD_4CHAN_2SEG_INTERLEAVED ' 4 Taps,2 Segments, each interleaved                |A,B,A,B,...,A,B|C,D,C,D,...,C,D|
        PCD_4CHAN_INTERLEAVE_CONVERGE '4 Taps,2 Segments converge, interleaved  |A,B,A,B,=>     |     <= C,D,C,D|
        PCD_2CHAN_SEP_TAP_CONVERGE      ' |A =>   |    <= B|
        PCD_SEP_QUAD_TAP_CONVERGE  ' 4TAPS - 4 QUADRANTS
        PCD_2TAP_INTERLINE_A_EVEN                       ' Tap A even lines Tap B odd lines
        PCD_2TAP_INTERLINE_B_EVEN                       ' Tap B even lines Tap A odd lines
        PCD_USER_DEFINED_GEO            ' a user-defined geometry
        PCD_NUM_GEOMETRY_KINDS
        PCD_INVALID_GEOMETRY = -1

End Enum

Enum PCD_DIVIDE_CTL_TYPE
        PCD_DISABLE_TRIG_DIVIDE = 0
        PCD_DIVIDE_TRIG_0 = 2
        PCD_DIVIDE_TRIG_1 = 3
End Enum

Enum PCD_EXSYNC_START_LOC_TYPE
        PCD_EXSYNC_START_CYCLE_END
        PCD_EXSYNC_START_CYCLE_BEGIN
        PCD_EXSYNC_START_MIDPOINT
End Enum

Enum PCD_PRI_START_LOC_TYPE
        PCD_PRI_START_CYCLE_BEGIN
        PCD_PRI_START_MIDPOINT
        PCD_PRI_START_CYCLE_END
End Enum

Enum PCD_PRI_END_LOC_TYPE
        PCD_PRI_END_AT_LEN_BEGIN
        PCD_PRI_END_AT_LEN_END
        PCD_PRI_END_IS_START_DEPEND
End Enum




Enum PCD_PARAMS_TYPE
        PCD_MULTI_ENABLE = &H5000&                      ' IFC_ENABLE_TYPE
        PCD_MULTI_POLARITY              ' IFC_POLARITY_TYPE

        PCD_MULTI_INPUT_MODE            ' IFC_MULTI_INPUT_TYPE

        PCD_PCLK_POLARITY               ' IFC_EDGE_TYPE

        PCD_MULTI_OUTPUT_ENABLE ' IFC_ENABLE_TYPE
        PCD_USE_EXT_MULTI               ' IFC_ENABLE_TYPE
        PCD_RETIME_ENABLE               ' IFC_ENABLE_TYPE

        PCD_RETIME_POLARITY             ' IFC_EDGE_TYPE

        PCD_CAM3_ENABLE                 ' IFC_ENABLE_TYPE

        PCD_EXSYNC_ENABLE               ' IFC_ENABLE_TYPE

        PCD_EXSYNC_POLARITY             ' IFC_POLARITY_TYPE

        PCD_EXSYNC_MODE                 ' IFC_EXSYNC_MODE

        PCD_PRI_ENABLE                  ' IFC_ENABLE_TYPE
        PCD_PRI_POLARITY                        ' IFC_POLARITY_TYPE
        
        PCD_CAM_MODE_CTL                        ' range 0..15
        PCD_EXT_SYNC_TIME               ' units are microseconds range 140ns - 572us
        PCD_EXT_SYNC_PERIOD_TIME        ' units are microseconds range 210ns - 18.75s
        PCD_CCLK_FREQ_SEL               '       range ???
        PCD_IMAGE_GEOMETRY              ' PCD_IMAGE_GEOMETRY_TYPE
        PCD_NUM_CAMERAS         ' range 1..3
        PCD_TRIG_GLITCH_DETECTOR ' IFC_ENABLE_TYPE
        PCD_CCLK_STATIC_ENABLE          ' IFC_ENABLE_TYPE
        PCD_CCLK_STATIC_STATE           ' IFC_LEVEL_TYPE
        PCD_EXO_FILENAME                ' String holding the filename
        PCD_TRIG_DIVIDE_FACTOR  ' Factor to scale trigger by
        PCD_TRIG_DIVIDE_CONTROL ' Which trigger if any divider is applied to
        PCD_USER_DEF_GEO_NAME   ' Name of user-defined geometry DLL
        PCD_EXSYNC_START_LOCATION ' PCD_EXSYNC_START_LOC_TYPE
        PCD_EXSYNC_MIDPOINT_DELAY ' units are microseconds range 140ns - 18.75s
        PCD_PRI_START_LOCATION  ' PCD_PRI_START_LOC_TYPE
        PCD_PRI_MIDPOINT_DELAY   ' units are microseconds range 140ns - 18.75s
        PCD_PRI_END_LOCATION    ' PCD_PRI_END_LOC_TYPE




        PCD_PARAM_END_MARKER
End Enum


Enum PCR_PIXEL_CLK_SRC_TYPE
        PCR_CAMERA_PIXEL_CLK
        PCR_PLL_PIXEL_CLK
        PCR_XTAL_PIXEL_CLK
End Enum

Enum PCR_HSYNC_SRC_TYPE
        PCR_CAMERA_COMPOSITE_HSYNC
        PCR_CAMERA_HSYNC
        PCR_PTG_HSYNC
        PCR_PTG_COMPOSITE_HSYNC
End Enum

Enum PCR_PWG_FLD_POL_TYPE
        PCR_LOW_IS_ODD
        PCR_LOW_IS_EVEN
End Enum

Enum PCR_FLD_SRC_TYPE
        PCR_FLD_SRC_SYNC_STRIPPER
        PCR_FLD_SRC_GENERATED_BASED_ON_H_AND_V_SYNC
End Enum

Enum PCR_LPF_TYPE
        PCR_LPF_DISABLE
        PCR_LPF_6MHZ
        PCR_LPF_10MHZ
End Enum

Enum PCR_GAIN_TYPE
        PCR_GAIN_FACTOR_2_AND_8_TENTHS
        PCR_GAIN_FACTOR_3_AND_4_TENTHS
End Enum

Enum PCR_SYNC_STRIPPER_SRC_TYPE
        PCR_GREEN_VIDEO_CHANNEL
        PCR_RED_VIDEO_CHANNEL
        PCR_BLUE_VIDEO_CHANNEL
        PCR_HSYNC_CHANNEL_0
        PCR_HSYNC_CHANNEL_1
End Enum

Enum PCR_CLAMP_SRC_TYPE
        PCR_SYNC_STRIPPER_BACK_PORCH
        PCR_PROGRAMMABLE
End Enum


Enum PCR_TRIG_SRC_TYPE
        PCR_SOFT_TRIG
        PCR_EXT_TRIG0
        PCR_EXT_TRIG1
        PCR_EXT_TRIG2
        PCR_OPTO_COUPLED_TRIG0
        PCR_OPTO_COUPLED_TRIG1
        PCR_RS422_DIFF_TRIG
End Enum



Enum PCR_PARAMS_TYPE

        PCR_FIELD_SRC = &H6000&                    ' IFC_ENABLE_TYPE
        PCR_SKIP_FIELD_MODE
        PCR_STROBE_OUTPUT_ENABLE
        PCR_FRAME_RESET_ON_VSYNC_OUTPUT
        PCR_TRIG_CYCLE_LATCH_TRIG
        PCR_RED_A_TO_D_PREF
        PCR_GREEN_A_TO_D_PREF
        PCR_BLUE_A_TO_D_PREF
        PCR_RED_A_TO_D_NREF
        PCR_GREEN_A_TO_D_NREF
        PCR_BLUE_A_TO_D_NREF
        PCR_LOW_PASS_FILTER
        PCR_PWG_FIELD_POLARITY
        PCR_FIELD_SHIFT
        PCR_PTG_VSYNC_OUT_EN
        PCR_CLAMP_SOURCE
        PCR_SYNC_STRIPPER_SOURCE
        PCR_BACK_PORCH_CLAMP_START
        PCR_BACK_PORCH_CLAMP_END
        PCR_NO_CLAMP_REGION
        PCR_PRGM_CLAMP_REF_POINT
        PCR_FRONT_PORCH_CLAMP_START
        PCR_FRONT_PORCH_CLAMP_END
        PCR_FRONT_PORCH_ENABLE
        PCR_MULTITAP_MODE
        PCR_EDONPISHA_MODE
        PCR_PTG2PWG_HSYNC_FLIP
        PCR_PARTIAL_SCAN_START
        PCR_PARTIAL_SCAN_END
        PCR_PARTIAL_SCAN_POLARITY
        PCR_PARTIAL_SCAN_MODE
        PCR_PARAM_END_MARKER
End Enum


Enum PCP_PWG_FLD_POL_TYPE
        PCP_LOW_IS_ODD
        PCP_LOW_IS_EVEN
End Enum

Enum PCP_FLD_SRC_TYPE
        PCP_FLD_SRC_SYNC_STRIPPER
        PCP_FLD_SRC_BASED_ON_H_AND_V_SYNC
End Enum

Enum PCP_LPF_TYPE
        PCP_LPF_6_5_MHZ
        PCP_LPF_12_5_MHZ
End Enum


Enum PCP_INTFLT_TYPE
        PCP_EXTERNAL_LOOP_FILTER
        PCP_INTERNAL_LOOP_FILTER
End Enum

Enum PCP_CLAMP_SRC_TYPE
        PCP_SYNC_STRIPPER_BACK_PORCH
        PCP_PROGRAMMABLE
End Enum

Enum PCP_VSCAN_CLOCKSEL
        PCP_VSCAN_CLKSEL_NORMAL
        PCP_VSCAN_CLKSEL_FRESET
End Enum


Enum PCP_TRIG_SRC_TYPE
        PCP_SOFT_TRIG
        PCP_EXT_TRIG0
        PCP_EXT_TRIG1
        PCP_EXT_TRIG2
        PCP_OPTO_COUPLED_TRIG0
        PCP_OPTO_COUPLED_TRIG1
        PCP_RS422_DIFF_TRIG0
        PCP_RS422_DIFF_TRIG1
End Enum


Enum PCP_PARAMS_TYPE
        PCP_FIELD_SRC = &H8000&

        PCP_SKIP_FIELD_MODE
        PCP_FRAME_RESET_ON_VSYNC_OUTPUT
        PCP_TRIG_CYCLE_LATCH_TRIG
        PCP_A_TO_D_PREF
        PCP_A_TO_D_NREF
        PCP_LOW_PASS_FILTER
        PCP_PWG_FIELD_POLARITY
        PCP_FIELD_SHIFT
        PCP_PTG_VSYNC_OUT_EN

        PCP_CLAMP_SOURCE
        PCP_BACK_PORCH_CLAMP_START
        PCP_BACK_PORCH_CLAMP_END
        PCP_NO_CLAMP_REGION
        PCP_PRGM_CLAMP_REF_POINT

        PCP_EDONPISHA_MODE
        PCP_PTG2PWG_HSYNC_FLIP
        PCP_OVERSAMPLE_MODE
        PCP_VSCAN_CLKSEL
        PCP_LOOP_FILTER
End Enum


Enum LNK_TRIG_SRC_TYPE
        LNK_DIFFERENTIAL_TRIG
        LNK_TTL_TRIG
        LNK_OPTO_COUPLED_TRIG
End Enum


Enum LNK_TRIG_MODE_TYPE
        LNK_TMODE_DISABLE = 0
        LNK_TMODE_HWTRIG0_ASSERT = 2
        LNK_TMODE_HWTRIG0_DEASSERT = 3
        LNK_TMODE_HWTRIG1_ASSERT = 4
        LNK_TMODE_HWTRIG1_DEASSERT = 5
        LNK_TMODE_SWTRIG0 = 6
        LNK_TMODE_SWTRIG1 = 7
End Enum


Enum LNK_DVAL_INPUT_TYPE
        LNK_DVAL_INPUT_FIELD
        LNK_DVAL_INPUT_VALID_DATA
End Enum


Enum LNK_EXSYNC_MODE_TYPE
        LNK_EXSYNC_FREE_RUNNING
        LNK_EXSYNC_TRIG1
        LNK_EXSYNC_TRIG2
        LNK_EXSYNC_SOFT_TRIG
        LNK_EXSYNC_SOFT_TRIG2
        LNK_EXSYNC_VB_TRIG
End Enum


Enum LNK_IMAGE_GEOMETRY_TYPE
        LNK_1CHAN_L2R
        LNK_2CHAN_INTERLEAVED
        LNK_2CHAN_SEP_TAP_L2R
        LNK_2CHAN_SEP_TAP_R2L
        LNK_4CHAN_SEP_TAP_L2R
        LNK_2CHAN_SEP_TAP_CONVERGE = 8
        LNK_2TAP_INTERLINE_A_EVEN = 10
        LNK_2TAP_INTERLINE_B_EVEN
        LNK_3CHAN_SEP_TAP_L2R
        LNK_USER_DEFINED_GEO

End Enum


Enum LNK_DIVIDE_CTL_TYPE
        LNK_DISABLE_TRIG_DIVIDE = 0
        LNK_DIVIDE_TRIG_0 = 2
        LNK_DIVIDE_TRIG_1 = 3
End Enum


Enum LNK_PRI_END_LOC_TYPE
        LNK_PRI_END_AT_LEN_BEGIN
        LNK_PRI_END_AT_LEN_END
        LNK_PRI_END_IS_START_DEPEND
End Enum


Enum LNK_LUT_BYTE_INPUT
        LNK_CAM_BYTE_0
        LNK_CAM_BYTE_1
        LNK_CAM_BYTE_2
        LNK_CAM_BYTE_ZERO
End Enum


Enum LNK_CAM_CTL_SELECT_TYPE
        LNK_CCTL_FIXED_LOW
        LNK_CCTL_FIXED_HIGH
        LNK_CCTL_EXSYNC
        LNK_CCTL_PRI
End Enum



Enum LNK_PARAMS_TYPE
        LNK_DVAL_ENABLE = &H9000&
        LNK_DVAL_POLARITY
        LNK_DVAL_INPUT_MODE

        LNK_SPR_ENABLE
        LNK_SPR_POLARITY

        LNK_EXSYNC_ENABLE

        LNK_EXSYNC_POLARITY

        LNK_EXSYNC_MODE

        LNK_PRI_ENABLE
        LNK_PRI_POLARITY
        
        LNK_EXT_SYNC_PERIOD_TIME
        LNK_EXT_SYNC_OFFSET_TIME
        LNK_EXT_SYNC_ACTIVE_TIME
        LNK_IMAGE_GEOMETRY
        LNK_NUM_CAMERAS
        LNK_TRIG_GLITCH_DETECTOR
        LNK_EXO_FILENAME
        LNK_TRIG_DIVIDE_FACTOR
        LNK_TRIG_DIVIDE_CONTROL
        LNK_USER_DEF_GEO_NAME
        LNK_PRI_OFFSET_TIME
        LNK_PRI_ACTIVE_TIME
        LNK_PRI_END_LOCATION
        LNK_LUT0_LOW_INPUT
        LNK_LUT0_HIGH_INPUT
        LNK_LUT1_LOW_INPUT
        LNK_LUT1_HIGH_INPUT
        LNK_CAM_CTL1_SIGNAL
        LNK_CAM_CTL2_SIGNAL
        LNK_CAM_CTL3_SIGNAL
        LNK_CAM_CTL4_SIGNAL
        LNK_SPATIAL_CORR_LINES
        LNK_SPATIAL_LEAD_COLOR
        LNK_TRIG_START_EVENT
        LNK_TRIG_STOP_EVENT
        LNK_FEN_PULSE
End Enum

Enum P2V_PARAMS_TYPE
        P2V_CLAMP_START = &H4000&
        P2V_CLAMP_END
        P2V_FIELD_PROCESS
        P2V_MASTER_HSYNC
        P2V_VS_PULSE_ENABLE
        P2V_VS_PULSE_OFFSET
        P2V_VS_PULSE_DURATION
        P2V_LOW_PASS_FILTER
        P2V_SYNC_SOURCE
        P2V_ADD_VSYNC_TO_FRAME_RESET
        P2V_ADD_FRAME_RESET_TO_VSYNC
        P2V_SELECT_UART_PORT
        P2V_HORZ_FRONT_PORCH
        P2V_HORZ_BACK_PORCH
        P2V_VSYNC_WAIT_COUNT
End Enum


Enum CL2_PARAMS_TYPE
        CL2_DVAL_ENABLE = &H7200&
        CL2_DVAL_INPUT_MODE

        CL2_EXSYNC_ENABLE
        CL2_EXSYNC_POLARITY

        CL2_EXT_SYNC_OFFSET_TIME
        CL2_EXT_SYNC_ACTIVE_TIME

        CL2_PRI_ENABLE
        CL2_PRI_POLARITY
        CL2_PRI_OFFSET_TIME
        CL2_PRI_ACTIVE_TIME

        CL2_IMAGE_GEOMETRY


        CL2_CAM_CTL1_SIGNAL
        CL2_CAM_CTL2_SIGNAL
        CL2_CAM_CTL3_SIGNAL
        CL2_CAM_CTL4_SIGNAL

        CL2_FRAME_TRIG_SRC
        CL2_FRAME_TRIG_FREQ

        CL2_VFRAME_TRIG_SOURCE

        CL2_LINE_TRIG_ENABLE
        CL2_LINE_TRIG_SRC
        CL2_LINE_TRIG_DROP_COUNT
        CL2_LINE_TRIG_NUM_PHASE
        CL2_LINE_TRIG_DEBOUNCE
        CL2_LINE_TRIG_CYCLE_TIME

        CL2_COMBINE_EXSYNC_PRI
        CL2_NLINES_INTR_COUNT
End Enum


'Enum PCV_TRIG_SRC_TYPE     ' use IFC_TRIG_SRC_TYPE instead
'       AMV_EXT_TRG
'        AMV_SFTW_TRG
'        AMV_TRGSRC_SKIP
'End Enum


Enum SRC_KIND
        NONE_SRC
        CAMERA_SRC
        HOST_BUFFER_SRC
        IMAGE_SRC
        LAST_SRC        'always last
End Enum

' sink kinds
Enum SINK_KIND
        NONE_SINK
        DIB_SINK
        DDRAW_SINK
        YCRCB_SINK
        IMAGE_SINK
        LAST_SINK       'keep this always last
End Enum

'overlay kinds
Enum OVERLAY_KIND
        NONE_OVERLAY
        SW_OVERLAY
        HW_OVERLAY
End Enum

Public Type CAM_ATTR
   dwWidth As Long
   dwHeight As Long
   dwBytesPerPixel As Long
   dwBitsPerPixel As Long
   color As IFC_COLOR
   xZoom As Single
   yZoom As Single
   camName(128 - 1) As Byte
End Type

Public Type IFC_PARAM_CAPS
   param As Integer
   presentationName As String
   paramName(80 - 1) As Byte
   paramType As IFC_PARAM_KIND
   dwArrayDim As Long
   memberGroupMask As Long
End Type

'* structure to return enumerated arguments */
Public Type IFC_ENUM_ARG
    argName As Long
    argValue As Long
    regValue As Long
End Type

Public Type IFC_GRAB_STATS
        NumberOfFramesLocked As Long
        NumberOfFramesLost As Long
        NumberOfFramesMissed As Long
        CurrentFrameSeqNum As Long
        NumberOfFramesAwaitDelivery As Long
End Type

Public Type IFC_GRABPHYS_STATS
        dwMinTimeConsec As Long
        dwMaxTimeConsec As Long
        dwNumBMDoneInterrupts As Long
End Type

Global Const MAX_MODNAME_LEN = 16
Global Const MAX_NUM_CHILD_MODS = 3

Public Type ITI_CHILD_MOD
        modName(MAX_MODNAME_LEN - 1) As Byte
        revision As Long
End Type

Public Type ITI_PARENT_MOD
        modName(MAX_MODNAME_LEN - 1) As Byte
        fullName(MAX_MODNAME_LEN - 1) As Byte
        seqnum As Long
        revision As Long
        PhysModPresent As Long
        child(MAX_NUM_CHILD_MODS - 1) As ITI_CHILD_MOD
        next As Long
End Type


Public Type IMGFILEPROPS
        Kind As Long
        dx As Long
        dy As Long
        bitsPerPixel As Integer
        imgClass As Long
        imgCompress As Long
End Type


Public Type GRAB_EXT_ATTR
        ArrivalTime As Double
        FrameSeqNum As Long
        FrameIsLocked As Long
        potentiallyBad As Long
End Type

Enum IFC_HW_PARAMS
    IFC_HW_ART_REV
    IFC_HW_ECO
    IFC_HW_SERIAL_NUM
    IFC_HW_DISP_KIND
    IFC_BRD_KIND
End Enum

Enum IFC_DEPTH
    IFC_PIX8 = 8
    IFC_PIX10 = 10
    IFC_PIX12 = 12
    IFC_PIX16 = 16
    IFC_PIX24 = 24
    IFC_PIX32 = 32
End Enum

Enum IFC_COLOR
    IFC_MONO
    IFC_RED
    IFC_GREEN
    IFC_BLUE
    IFC_RGB
    IFC_RGB_PACK24
    IFC_MONO_WORD_LO
    IFC_MONO_WORD_HI
    IFC_RGB_PLANAR
    IFC_aRGB_PLANAR
    IFC_YCRCB
    IFC_YCRCBMONO
    IFC_NUM_COLOR_MODES ' Always keep last
End Enum

'typedef void *HIFCGRAB;


'/* Field status defines */
Enum IFC_FIELD_STATUS
    IFC_EVEN_FIELD '                       /* Field status is even */
    IFC_ODD_FIELD '                        /* Field status is odd */
    IFC_NEXT_FIELD '                       /* Next field acquisition */
End Enum

'/* Scan Mode status defines */
Enum IFC_ILACE
    IFC_NILACED '    /* Scan Mode is No interlace */
    IFC_ILACED  '    /* Scan Mode is Interlaced */
End Enum


Declare Sub CICamera_ReleaseCamFrame Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal pFrame As Long)
Declare Function CICamera_GetCamFrame Lib "ifcapi.dll" (ByVal pCamera As Long) As Long
Declare Function CICamera_CreateInterruptObject Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT) As Long
Declare Sub CICamera_UpdateParams Lib "ifcapi.dll" (ByVal pCamera As Long)
Declare Function CICamera_AcqParamSupported Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long) As Integer
Declare Function CICamera_GetAcqParam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal index As Long) As Double
Declare Sub CICamera_SetAcqParam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal value As Double, ByVal index As Long)
'Declare Sub CICamera_GetParamCaps lib "ifcapi.dll" (ByVal pCamera As Long,ByVal paramID As Long,PIFC_PARAM_CAPS lpParamCaps)
Declare Function CICamera_GetFirstParam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramGroupMask As Long) As Integer
Declare Function CICamera_GetNextParam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal paramGroupMask As Long) As Integer
Declare Function CICamera_GetFirstParamGroup Lib "ifcapi.dll" (ByVal pCamera As Long) As IFC_PARAM_GROUP_TYPE
Declare Function CICamera_GetNextParamGroup Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal groupID As IFC_PARAM_GROUP_TYPE) As IFC_PARAM_GROUP_TYPE
'Declare Sub CICamera_GetGroupProperties lib "ifcapi.dll" (ByVal pCamera As Long,ByVal groupID As IFC_PARAM_GROUP_TYPE ,PIFC_PARAM_GROUP_PROPS lpGroupProps)
Declare Function CICamera_GetFirstEnumArg Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByRef arg As IFC_ENUM_ARG) As Integer
Declare Function CICamera_GetNextEnumArg Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByRef arg As IFC_ENUM_ARG) As Integer
Declare Function CICamera_IsArgSupported Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal arg As Double) As Integer
Declare Function CICamera_ClosestArgSupported Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal arg As Double) As Double
Declare Function CICamera_GetArgName Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal dArg As Double) As Long
Declare Function CICamera_GetArgValue Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long, ByVal szArgName As String) As Double
Declare Function CICamera_SetLutSub Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal func As Long, ByRef constants As Long, ByVal lutPortion As LUT_PORTION_TYPE) As Integer
Declare Sub CICamera_ReadLutBuf Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutAdr As Long, ByVal numEntries As Long, ByRef buf As Byte, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_WriteLutBuf Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutAdr As Long, ByVal numEntries As Long, ByRef buf As Byte, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Function CICamera_ReadLutLoc Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutAdr As Long, ByVal lutPortion As LUT_PORTION_TYPE) As Long
Declare Sub CICamera_WriteLutLoc Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutAdr As Long, ByVal val As Long, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_LinearizeLut Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_FloodLUT Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal val As Long, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_InvertLut Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_ThresholdLut Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal dwThreshold As Long, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_OffsetLut Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lOffset As Long, ByVal lutPortion As LUT_PORTION_TYPE)
Declare Sub CICamera_RgbToHsiLUT Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutIS As LUTID_TYPE, ByVal lutPortion As LUT_PORTION_TYPE)
'Declare Sub CICamera_GetLUTCaps lib "ifcapi.dll" (ByVal pCamera As Long,LPLUTCAP caps)
'Declare Sub CICamera_SetLutPathPage lib "ifcapi.dll" (ByVal pCamera As Long,ByVal lutIS As LUTID_TYPE,IFC_LUT_PIX_SIZE_TYPE pxSize,ByVal pageNum As Long)
'Declare Sub CICamera_SetLutHostPage lib "ifcapi.dll" (ByVal pCamera As Long,ByVal lutIS As LUTID_TYPE,IFC_LUT_PIX_SIZE_TYPE pxSize,ByVal pageNum As Long,ByVal leftJustify As Boolean)
Declare Sub CICamera_SetWindowGen Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer)
Declare Function CICamera_SetCameraType Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal camName As String, ByVal updateHW As Boolean) As Integer
Declare Function CICamera_GetNextCamType Lib "ifcapi.dll" (ByVal pCamera As Long) As Long
Declare Function CICamera_GetFirstCamType Lib "ifcapi.dll" (ByVal pCamera As Long) As Long
Declare Function CICamera_Freeze Lib "ifcapi.dll" (ByVal pCamera As Long) As Integer
Declare Function CICamera_FreezeEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long) As Integer
Declare Sub CICamera_Snap Lib "ifcapi.dll" (ByVal pCamera As Long)
Declare Sub CICamera_Grab Lib "ifcapi.dll" (ByVal pCamera As Long)
Declare Function CICamera_Grab_HostBuf Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef dest As Byte, ByVal ringNumFrames As Long, ByVal totalNumFrames As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Long
Declare Function CICamera_Grab_HostBufEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal dwOptions As Long, ByRef dest As Byte, ByVal ringNumFrames As Long, ByVal totalNumFrames As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Long
Declare Sub CICamera_GrabLock Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal seqnum As Long)
Declare Sub CICamera_GrabLockEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByVal seqnum As Long)
Declare Sub CICamera_GrabRelease Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal seqnum As Long)
Declare Sub CICamera_GrabReleaseEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByVal seqnum As Long)
Declare Function CICamera_GrabWaitFrame Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef frameAddr As Long, ByVal FrameSeqNum As Long, ByVal milliseconds As Long, ByVal lockFrame As Long, ByRef acquiredDy As Long) As Long
Declare Function CICamera_GrabWaitFrameEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByRef frameAddr As Long, ByVal FrameSeqNum As Long, ByVal milliseconds As Long, ByVal lockFrame As Long, ByRef acquiredDy As Long, ByRef ExtendedAttr As Long) As Long
Declare Function CICamera_GrabFrameSeqNum Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal frameRingNum As Integer) As Integer
Declare Function CICamera_GrabFrameSeqNumEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByVal frameRingNum As Integer) As Integer
Declare Function CICamera_GetGrabStats Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByRef stats As IFC_GRAB_STATS) As Integer
Declare Function CICamera_GrabGetExtAttr Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal grabID As Long, ByVal seqnum As Long, ByRef ExtendedAttr As GRAB_EXT_ATTR) As Integer

Declare Function CICamera_Snap_HostBuf Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef dest As Byte, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function CICamera_SeqSnap Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef dest As Byte, ByVal numFrames As Integer, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal dwMilliseconds As Long) As Integer
Declare Function CICamera_SeqSnapPhys Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal numFrames As Long, ByVal destOffset As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal dwMilliseconds As Long, ByRef acquiredDys As Long) As Long
Declare Function CICamera_WaitPhysFrame Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef frameAddr As Long, ByVal FrameSeqNum As Long, ByVal dwMilliseconds As Long, ByRef acquiredDy As Long) As Long
Declare Function CICapMod_GetGrabPhysStats Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef stats As IFC_GRABPHYS_STATS) As Long


Declare Function CICamera_TrigRead Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByRef dest As Byte) As Integer
Declare Function CICamera_WaitTrig Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal waitTime As Long) As Integer
Declare Function CICamera_TrigSnap Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal trigSource As Long) As Integer
Declare Function CICamera_StartTrigOps Lib "ifcapi.dll" (ByVal pCamera As Long) As Integer
Declare Function CICamera_StopTrigOps Lib "ifcapi.dll" (ByVal pCamera As Long) As Integer
Declare Function CICamera_SetZoom Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal xZoom As Single, ByVal yZoom As Single) As Integer
'Declare Sub CICamera_GetZoomCaps lib "ifcapi.dll" (ByVal pCamera As Long,LPZOOMCAP lpCaps)
Declare Function CICamera_ReadArea Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByRef destadr As Byte, ByVal dest_dx As Long, ByVal readOptions As Long) As Integer
Declare Sub CICamera_LineReverseRead Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal destlinebytes As Integer, ByRef destadr As Byte, ByVal readOptions As Long)
Declare Sub CICamera_ReadDestPitchArea Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal destlinebytes As Integer, ByVal physdest As Long, ByVal readOptions As Long)
Declare Sub CICamera_GetAttr Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef lpAttr As CAM_ATTR, ByVal zoomCorrected As Boolean)
'Declare Sub CICamera_GetReadCaps lib "ifcapi.dll" (ByVal pCamera As Long,LPREADCAP lpCaps)
Declare Sub CICamera_SetReadColorRemap Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal bEnabled As Boolean)
Declare Function CICamera_ReadReg Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal reg As Long) As Long
Declare Sub CICamera_WriteReg Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal reg As Long, ByVal val As Long)
'Declare Function CICamera_UpdateParamFromCfg lib "ifcapi.dll" (ByVal pCamera As Long,ByVal cfg As Long,IFC_PARAM_KIND parmType,ByVal numVals As Long,ByRef  paramVal As Double) As Integer
'Declare Function CICamera_WriteParamToCfg lib "ifcapi.dll" (ByVal pCamera As Long,ByVal cfg As Long, IFC_PARAM_KIND parmType, ByVal numVals As Long, ByRef  paramVal As Double) As Integer
Declare Function CICamera_WriteUartCommand Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef cmd As Byte, ByVal numBytes As Long, ByVal uartIndex As Long) As Long
Declare Function CICamera_ReadUartCommand Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef cmd As Byte, ByVal numBytesToRead As Long, ByRef numBytesRead As Long, ByVal uartIndex As Long) As Long
Declare Function CICamera_UartCommandResponse Lib "ifcapi.dll" (ByVal pCamera As Long, ByRef cmd As Byte, ByVal numCmdBytes As Long, ByRef response As Byte, ByVal numBytesToRead As Long, ByRef numBytesRead As Long, ByVal uartIndex As Long) As Long
Declare Function CICamera_Grab_HostBufListEx Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal dwOptions As Long, ByRef dests As Long, ByVal ringNumFrames As Long, ByVal totalNumFrames As Long, ByVal x As Long, ByVal y As Long, ByVal dx As Long, ByVal dy As Long) As Long
Declare Function CICamera_GetCurrentTransform Lib "ifcapi.dll" (ByVal pCamera As Long) As Long
Declare Function CICamera_GetParamAlias Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal paramID As Long) As Long
Declare Function CICamera_GetPortNum Lib "ifcapi.dll" (ByVal pCamera As Long) As Long
Declare Sub CICamera_LutPassMostSigBits Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal lutID As LUTID_TYPE, ByVal lutPortion As LUT_PORTION_TYPE, ByVal numBitsToPass As Long)
Declare Function CICamera_SetTransform Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal eTransform As IFC_TRANSFORM_TYPE) As Long
Declare Function CICamera_TransformSupported Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal eTransform As IFC_TRANSFORM_TYPE) As Long


Declare Function CICapMod_CreateInterruptObject Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT) As Long
Declare Function CICapMod_CreateSeqFrame Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal frameCnt As Integer, ByRef frames As Long, ByVal dx As Long, ByVal dy As Long, ByVal depth As IFC_DEPTH, ByVal color As IFC_COLOR) As Integer
Declare Function CICapMod_CreateFrame Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal dx As Long, ByVal dy As Long, ByVal depth As IFC_DEPTH, ByVal color As IFC_COLOR) As Long
Declare Sub CICapMod_DeleteAllFrames Lib "ifcapi.dll" (ByVal CapMod As Long)
Declare Sub CICapMod_Cleanup Lib "ifcapi.dll" (ByVal CapMod As Long)
Declare Function CICapMod_GetCamFrame Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long) As Long
Declare Sub CICapMod_ReleaseCamFrame Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal pFrame As Long)
Declare Sub CICapMod_GrabRelease Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal grabID As Long, ByVal seqnum As Integer)
Declare Sub CICapMod_GrabLock Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal grabID As Long, ByVal seqnum As Integer)
Declare Function CICapMod_GrabStop Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal grabID As Long) As Integer
Declare Function CICapMod_GrabWaitFrame Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal grabID As Long, ByRef frameAddr As Byte, ByVal FrameSeqNum As Integer, ByVal milliseconds As Long, ByVal block As Boolean, ByRef acquiredDy As Long) As Integer
Declare Function CICapMod_Grab_HostBuf Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal dwModes As Long, ByRef dest As Byte, ByVal ringNumFrames As Integer, ByVal totalNumFrames As Integer, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Long
Declare Function CICapMod_GrabFrameSeqNum Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal grabID As Long, ByVal frameRingNum As Integer) As Integer
Declare Function CICapMod_SeqSnap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByRef dest As Byte, ByVal numFrames As Integer, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function CICapMod_Snap_HostBuf Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByRef dest As Byte, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer) As Integer
Declare Function CICapMod_StartTrigOps Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long) As Long
Declare Function CICapMod_TrigRead Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal trigOp As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByRef dest As Byte) As Long
Declare Function CICapMod_WaitTrig Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal trigOp As Long, ByVal waitTime As Long) As Long
Declare Function CICapMod_TrigSnap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal trigOp As Long, ByVal trigSource As Long) As Long
Declare Function CICapMod_StopTrigOps Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal trigOp As Long) As Long
Declare Function CICapMod_SetZoom Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal xZoom, ByVal yZoom As Single) As Integer
'Declare Sub CICapMod_GetZoomCaps lib "ifcapi.dll" (ByVal capMod As Long,ByVal pCamera As Long,LPZOOMCAP lpCaps)
'Declare Sub CICapMod_GetReadCaps lib "ifcapi.dll" (ByVal capMod As Long,LPREADCAP lpCaps)
Declare Sub CICapMod_SetReadColorRemap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal bEnabled As Boolean)
Declare Sub CICapMod_Freeze Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long)
Declare Sub CICapMod_Snap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long)
Declare Sub CICapMod_Grab Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long)
Declare Sub CICapMod_ReleaseCamMutex Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long)
Declare Function CICapMod_GetCamMutex Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long) As Long
Declare Function CICapMod_GetCam Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal camPortNum As Long) As Long
Declare Function CICapMod_Create Lib "ifcapi.dll" (ByVal CapMod As Long, ByRef modName As Byte, ByVal seqnum As Long) As Integer
Declare Function CICapMod_Create_FromConfig Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal seqnum As Long, ByRef cfgFile As Byte) As Integer
'Declare Function CICapMod_WriteConfigFile lib "ifcapi.dll" (ByVal capMod As Long,const ByRef szCfgFileName As BYTE, IFC_CFG_CAMERA_SPECIFIER eCamFlag ) As Integer
'Declare Function CICapMod_WriteConfigFile_CamName lib "ifcapi.dll" (ByVal capMod As Long,const ByRef szCfgFileName As BYTE, const ByRef szCameraName As BYTE) As Integer
Declare Function CICapMod_OutportStrobeVal Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal val As IFC_LEVEL_TYPE, ByVal channelNum As Long) As Integer
Declare Sub CICapMod_OutportVal Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal val As Integer, ByVal channelNum As Long)
Declare Sub CICapMod_InportMode Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal strobed As Boolean, ByVal latchEdge As IFC_EDGE_TYPE, ByVal channelNum As Long)
Declare Function CICapMod_InportVal Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal channelNum As Long) As Integer
Declare Function CICapMod_InportInterruptPolarity Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal intrEdge As IFC_EDGE_TYPE, ByVal channelNum As Long) As Integer
Declare Function CICapMod_SnapAsync Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long) As Integer
Declare Function CICapMod_SeqSnapAsync Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal frameCnt As Long, ByRef frames As Long) As Integer
Declare Function CICapMod_Acqbits Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long, ByVal mode As Integer) As Integer
Declare Function CICapMod_WaitStartVB Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long) As Integer
Declare Function CICapMod_WaitVertBlank Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long) As Integer
Declare Function CICapMod_WaitNotVB Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long, ByVal vbsync As Boolean) As Integer
Declare Function CICapMod_WaitAcq Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pFrame As Long) As Integer
Declare Sub CICapMod_ReadDestPitchArea Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal destlinebytes As Integer, ByVal physdest As Long, ByVal readOptions As Long)
Declare Function CICapMod_LineReverseRead Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal destlinebytes As Integer, ByRef destadr As Byte, ByVal readOptions As Long) As Integer
Declare Function CICapMod_ReadArea Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal pCamera As Long, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByRef destadr As Byte, ByVal dest_dx As Long, ByVal readOptions As Long) As Integer
Declare Function CICapMod_ReadPerformance Lib "ifcapi.dll" (ByVal CapMod As Long) As Single
Declare Function CICapMod_FindCameraType Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal camName As String) As Long
Declare Sub CICapMod_ProcessCameraFileList Lib "ifcapi.dll" (ByVal CapMod As Long, ByRef szListFileName As Byte)
Declare Sub CICapMod_ProcessCameraFilesInDir Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal szPath As String, ByVal bRecurse As Boolean)
Declare Function CICapMod_GetFirstCamType Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CICapMod_GetNextCamType Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CICapMod_AddCameraType Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal strNewCamName As String, ByVal strExistingCamName As String) As Long
Declare Function CICapMod_ContiguousMemAvailable Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CICapMod_EnableJitGrabMemLock Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CICapMod_GetAcqTimeout Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CICapMod_SetAcqTimeout Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal dwMilliseconds As Long) As Long
Declare Function CICapMod_LockMem Lib "ifcapi.dll" (ByVal CapMod As Long, ByRef ptr As Byte, ByVal dwSize As Long) As Long
Declare Sub CICapMod_UnLockMem Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal memLockHandle As Long)

Declare Sub CImgConn_Display Lib "ifcapi.dll" (ByVal imgConn As Long)
Declare Function CImgConn_Create Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_StartLiveImage Lib "ifcapi.dll" (ByVal imgConn As Long, ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT, ByVal InterruptScale As Integer) As Integer
Declare Function CImgConn_StopLiveImage Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_LiveImageSuspend Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_LiveImageResume Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_GetLiveImageFPS Lib "ifcapi.dll" (ByVal imgConn As Long) As Double
Declare Function CImgConn_GetOverlayDC Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Sub CImgConn_ReleaseOverlayDC Lib "ifcapi.dll" (ByVal imgConn As Long, ByVal hDC As Long)
Declare Sub CImgConn_EnableOverlay Lib "ifcapi.dll" (ByVal imgConn As Long, ByVal bEnable As Boolean)
'Declare Function CImgConn_GetImgServer lib "ifcapi.dll" (ByVal imgConn As Long) As 'CCallBackServer
Declare Function CImgConn_GetSrc Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Function CImgConn_GetSink Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Function CImgConn_GetOverlay Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Function CImgConn_GetOverlayWidth Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_GetOverlayHeight Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_GetOverlayMaxStretch Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Function CImgConn_GetOverlayBitsPP Lib "ifcapi.dll" (ByVal imgConn As Long) As Integer
Declare Function CImgConn_GetOverlayMinStretch Lib "ifcapi.dll" (ByVal imgConn As Long) As Long
Declare Function CImgConn_GetOverlayKind Lib "ifcapi.dll" (ByVal imgConn As Long) As OVERLAY_KIND
Declare Function CImgFile_ReadFile Lib "ifcapi.dll" (ByVal imgFile As Long, ByRef dest As Byte) As Integer
Declare Function CImgFile_WriteFile Lib "ifcapi.dll" (ByVal imgFile As Long, ByRef src As Byte, ByVal dx As Long, ByVal dy As Long, ByVal bitsPerPixel As Integer, ByVal imgClass As IFFCLASS_TYPE, ByVal imgCompress As IFFCOMPRESSION_TYPE) As Integer
'Declare Function CImgFile_ImageFileProps lib "ifcapi.dll" (ByVal imgFile As Long,LPIMGFILEPROPS props) As Integer
Declare Function CImgSink_GetAoiStartX Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_GetAoiStartY Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_GetWidth Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_GetHeight Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_GetLinePitch Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Sub CImgSink_SetAoiPos Lib "ifcapi.dll" (ByVal imgSink As Long, ByVal wxAoiStart As Integer, ByVal wyAoiStart As Integer)
Declare Sub CImgSink_GetAoiPos Lib "ifcapi.dll" (ByVal imgSink As Long, ByRef pwxAoiStart As Integer, ByRef pwyAoiStart As Integer)
Declare Function CImgSink_GetSinkWindow Lib "ifcapi.dll" (ByVal imgSink As Long) As Long
Declare Sub CImgSink_GetZoom Lib "ifcapi.dll" (ByVal imgSink As Long, ByRef ZoomX As Double, ByRef ZoomY As Double)
Declare Sub CImgSink_SetZoom Lib "ifcapi.dll" (ByVal imgSink As Long, ByVal ZoomX As Double, ByVal ZoomY As Double)
Declare Function CImgSink_GetZoomX Lib "ifcapi.dll" (ByVal imgSink As Long) As Double
Declare Function CImgSink_GetZoomY Lib "ifcapi.dll" (ByVal imgSink As Long) As Double
Declare Function CImgSink_ResizeWindow Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_Create Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_MakeCopy Lib "ifcapi.dll" (ByVal imgSink As Long) As Long
Declare Function CImgSink_GetBufferAddr Lib "ifcapi.dll" (ByVal imgSink As Long) As String
Declare Function CImgSink_GetBitsPP Lib "ifcapi.dll" (ByVal imgSink As Long) As Integer
Declare Function CImgSink_GetMinStretch Lib "ifcapi.dll" (ByVal imgSink As Long) As Long
Declare Function CImgSink_GetMaxStretch Lib "ifcapi.dll" (ByVal imgSink As Long) As Long
Declare Function CImgSink_SetDestColorKey Lib "ifcapi.dll" (ByVal imgSink As Long, ByVal dwNewColorKey As Long) As Integer
Declare Function CImgSink_SetRemapColor Lib "ifcapi.dll" (ByVal imgSink As Long, ByVal iFirstIndex As Integer, ByVal iLastIndex As Integer, ByVal RemapColor As Long) As Integer
Declare Function CImgSink_GetDestColorKey Lib "ifcapi.dll" (ByVal imgSink As Long) As Long
Declare Function CImgSink_GetColorKeyRep Lib "ifcapi.dll" (ByVal imgSink As Long, ByVal color As Long) As Long
Declare Function CImgSink_GetKind Lib "ifcapi.dll" (ByVal imgSink As Long) As SINK_KIND
Declare Function CImgSrc_Create Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_FrameWidth Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_FrameHeight Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Sub CImgSrc_SetAoiPos Lib "ifcapi.dll" (ByVal imgSrc As Long, ByVal wxAoiStart As Integer, ByVal wyAoiStart As Integer)
Declare Sub CImgSrc_GetAoiPos Lib "ifcapi.dll" (ByVal imgSrc As Long, ByRef pwxAoiStart As Integer, ByRef pwyAoiStart As Integer)
Declare Function CImgSrc_GetAoiStartX Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetAoiStartY Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetWidth Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetHeight Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetLinePitch Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetBitsPP Lib "ifcapi.dll" (ByVal imgSrc As Long) As Integer
Declare Function CImgSrc_GetColor Lib "ifcapi.dll" (ByVal imgSrc As Long) As IFC_COLOR
Declare Function CImgSrc_GetKind Lib "ifcapi.dll" (ByVal imgSrc As Long) As SRC_KIND
Declare Function CImgSrc_GetCamera Lib "ifcapi.dll" (ByVal imgSrc As Long) As Long
Declare Function CImgSrc_GetBufferAddr Lib "ifcapi.dll" (ByVal imgSrc As Long) As String
Declare Sub CImgSrc_SetBufferAddr Lib "ifcapi.dll" (ByVal imgSrc As Long, ByVal pBuffer As Long)
Declare Function CImgSrc_SetOptions Lib "ifcapi.dll" (ByVal imgSrc As Long, ByVal options As Long) As Long
Declare Function CInterrupt_Connected Lib "ifcapi.dll" (ByVal intr As Long) As Integer
Declare Function CInterrupt_Clear Lib "ifcapi.dll" (ByVal intr As Long) As Integer
Declare Function CInterrupt_Wait Lib "ifcapi.dll" (ByVal intr As Long, ByVal dwMilliseconds As Long) As Integer
'Declare Function CInterrupt_WaitIntrOrEventSet lib "ifcapi.dll" (ByVal intr As Long,ByVal dwMilliseconds As Long, OS_event_t event1, OS_event_t event2, OS_event_t event3) As IFC_INTR_WAIT_TYPE
Declare Sub CInterrupt_Rearm Lib "ifcapi.dll" (ByVal intr As Long)
Declare Function CInterrupt_EventLong Lib "ifcapi.dll" (ByVal intr As Long) As Long
Declare Function COverlay_Create Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_GetOverlayDC Lib "ifcapi.dll" (ByVal Overlay As Long) As Long
Declare Sub COverlay_ReleaseOverlayDC Lib "ifcapi.dll" (ByVal Overlay As Long, ByVal hDC As Long)
Declare Function COverlay_GetBitsPP Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_GetWidth Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_GetHeight Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_GetMinStretch Lib "ifcapi.dll" (ByVal Overlay As Long) As Long
Declare Function COverlay_GetMaxStretch Lib "ifcapi.dll" (ByVal Overlay As Long) As Long
Declare Function COverlay_LockOverlay Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_UnlockOverlay Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function COverlay_GetKind Lib "ifcapi.dll" (ByVal Overlay As Long) As OVERLAY_KIND
Declare Sub COverlay_Enable Lib "ifcapi.dll" (ByVal Overlay As Long, ByVal bEnable As Boolean)
Declare Function COverlay_IsEnabled Lib "ifcapi.dll" (ByVal Overlay As Long) As Integer
Declare Function CPCDig_SetAcqTriggerEvents Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal startEvent As PCD_TRIG_MODE_TYPE, ByVal stopEvent As PCD_TRIG_MODE_TYPE, ByVal numFramesPerTrig As Long) As Integer
Declare Function IFC_IfxCreateCaptureModule Lib "ifcapi.dll" (ByVal modName As String, ByVal seqnum As Long, ByVal cfgFile As String) As Long
Declare Function IFC_IfxCreateImgConn_Cam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal hwnd As Long, ByVal Flags As Long, ByVal intrEvent As ICAP_INTR_EVENT, ByVal iScale As Integer) As Long
Declare Function IFC_IfxCreateImgConn_HostBuf Lib "ifcapi.dll" (ByRef pImgBuffer As Byte, ByVal wWidth As Integer, ByVal wHeight As Integer, ByVal wImgBitsPP As Integer, ByVal hwnd As Long, ByVal eColor As IFC_COLOR, ByVal Flags As Long, ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT, ByVal iScale As Integer, ByVal pFunc As Long, ByRef pArg As Byte) As Long
Declare Function IFC_IfxCreateImgConn Lib "ifcapi.dll" (ByVal imgSrc As Long, ByVal imgSink As Long, ByVal Flags As Long, ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT, ByVal iScale As Integer) As Long
Declare Function IFC_IfxCreateImgConn_WithOverlay Lib "ifcapi.dll" (ByVal imgSrc As Long, ByVal imgSink As Long, ByVal Overlay As Long, ByVal Flags As Long, ByVal pCamera As Long, ByVal intrEvent As ICAP_INTR_EVENT, ByVal iScale As Integer) As Long
Declare Function IFC_IfxCreateImgSrc_HostBuf Lib "ifcapi.dll" (ByRef pImgBuffer As Byte, ByRef pCamAttr As CAM_ATTR) As Long
Declare Function IFC_IfxCreateImgSrc_Area Lib "ifcapi.dll" (ByRef pImgBuffer As Byte, ByVal wWidth As Integer, ByVal wHeight As Integer, ByVal wImgBitsPP As Integer, ByVal eColor As IFC_COLOR, ByVal wxAoiStart As Integer, ByVal wyAoiStart As Integer, ByVal wAoiWidth As Integer, ByVal wAoiHeight As Integer) As Long
Declare Function IFC_IfxCreateImgSrc_Cam Lib "ifcapi.dll" (ByVal pCamera As Long, ByVal wxAoiStart As Integer, ByVal wyAoiStart As Integer, ByVal wAoiWidth As Integer, ByVal wAoiHeight As Integer) As Long
Declare Function IFC_IfxCreateImgSink Lib "ifcapi.dll" (ByVal hwnd As Long, ByVal Kind As SINK_KIND, ByVal wSinkStartX As Integer, ByVal wSinkStartY As Integer, ByVal width As Integer, ByVal height As Integer) As Long
Declare Function IFC_IfxCreateOverlay Lib "ifcapi.dll" (ByVal Kind As OVERLAY_KIND, ByVal wWidth As Integer, ByVal wHeight As Integer) As Long
Declare Function IFC_IfxCreateImgFile Lib "ifcapi.dll" (ByVal fileName As String) As Long
Declare Sub IFC_IfxDeleteImgSrc Lib "ifcapi.dll" (ByVal pImgSrc As Long)
Declare Sub IFC_IfxDeleteImgSink Lib "ifcapi.dll" (ByVal pImgSink As Long)
Declare Sub IFC_IfxDeleteImgConn Lib "ifcapi.dll" (ByVal pImgConn As Long)
Declare Sub IFC_IfxDeleteOverlay Lib "ifcapi.dll" (ByVal pOverlay As Long)
Declare Sub IFC_IfxDeleteImgFile Lib "ifcapi.dll" (ByVal pImgFile As Long)
Declare Sub IFC_IfxDeleteCaptureModule Lib "ifcapi.dll" (ByVal pCapMod As Long)
Declare Function IFC_IfxGetLastError Lib "ifcapi.dll" () As Long
Declare Sub IFC_IfxSetConsoleHandler Lib "ifcapi.dll" (ByVal pfCONSOLEHDLR As Long)
Declare Function IFC_IfxCreateInterrupt Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal intrEvent As Long) As Long
Declare Function IFC_IfxCreateVirtualParentModule Lib "ifcapi.dll" (ByVal modName As String, ByVal seqnum As Long, ByVal cfgFile As String, ByVal DaughterModNames As String) As Long
Declare Function IFC_IfxWriteImgFile Lib "ifcapi.dll" (ByVal fileName As String, ByRef src As Byte, ByVal dx As Long, ByVal dy As Long, ByVal bitsPerPixel As Integer, ByVal imgClass As IFFCLASS_TYPE, ByVal imgCompress As IFFCOMPRESSION_TYPE) As Long
Declare Function IFC_IfxReadImgFile Lib "ifcapi.dll" (ByVal fileName As String, ByRef dest As Byte, ByRef props As IMGFILEPROPS) As Long
Declare Function IFC_IfxCreateITIMods Lib "ifcapi.dll" () As Long
Declare Sub IFC_IfxDeleteITIMods Lib "ifcapi.dll" (ByVal itiMods As Long)




Declare Function CModule_ModName2 Lib "ifcapi.dll" Alias "CModule_ModName" (ByVal Pmod As Long) As Long
Declare Function CModule_IfxGetBoardParam Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal eParamId As IFC_HW_PARAMS, ByRef param As Long) As Long
Declare Function CModule_Revision Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CModule_GetLastError Lib "ifcapi.dll" (ByVal pClass As Long) As Long

Declare Function IFC_strcpy Lib "ifcapi.dll" (ByVal Outstr As String, ByVal Instr As Long) As String

Declare Function CITIMods_GetFirst Lib "ifcapi.dll" (ByVal itiMods As Long, ByRef modDesc As ITI_PARENT_MOD) As Long
Declare Function CITIMods_GetNext Lib "ifcapi.dll" (ByVal itiMods As Long, ByRef modDesc As ITI_PARENT_MOD) As Long

Declare Function CIFCOS_GetSystimeMicrosecs Lib "ifcapi.dll" () As Double
Declare Function CIFCOS_GetSystimeMillisecs Lib "ifcapi.dll" () As Double


Declare Function IFC_IfxCreateIntrCallback Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal intrEvent As Long, ByVal lpStartAddress As Long, ByVal lpParameter As Long) As Long
Declare Sub IFC_IfxDeleteIntrCallback Lib "ifcapi.dll" (ByVal callBack As Long)

Declare Function CPCVision2_SwitchCameraDefineStart Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CPCVision2_SwitchCameraDefineEnd Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CPCVision2_SwitchCameraGrab Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CPCVision2_SwitchCameraSnap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal numFrames As Long) As Long
Declare Function CPCVision2_SwitchCameraFreeze Lib "ifcapi.dll" (ByVal CapMod As Long) As Long
Declare Function CPCVision2_SetFrameDelaySequence Lib "ifcapi.dll" (ByVal CapMod As Long, ByRef camPortSeq As Long, ByVal numCameras As Long, ByVal trigSrc As IFC_TRIG_SRC_TYPE) As Long
Declare Function CPCVision2_FrameDelaySnap Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal trigSrc As IFC_TRIG_SRC_TYPE, ByRef dest As Byte, ByVal x As Integer, ByVal y As Integer, ByVal dx As Integer, ByVal dy As Integer, ByVal dwMilliseconds As Long) As Long
Declare Function CPCVision2_FrameDelayWait Lib "ifcapi.dll" (ByVal CapMod As Long, ByVal dwMilliseconds As Long) As Long



Public Function CModule_ModName(ByVal Pmod As Long) As String
    Dim tempstr As String
    tempstr = String(255, vbNullChar)

    IFC_strcpy tempstr, CModule_ModName2(Pmod)
    CModule_ModName = tempstr
End Function

