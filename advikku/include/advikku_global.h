#include <stdint.h>
#include <tonc.h>

#ifndef ADVIKKU_GLOBAL
#define ADVIKKU_GLOBAL

// --------------------------------------------------------------------
// GLOBAL PLAYER VARIABLES
// --------------------------------------------------------------------

// Advikku variables
extern uint16_t advik_start;
extern uint16_t advik_loop_point;
extern uint16_t advik_ticks_per_row_counter;
extern uint16_t advik_ticks_per_row_value;
extern uint16_t advik_current;
extern uint16_t advik_future;
extern uint16_t advik_global_order_number;
extern uint16_t advik_global_order_length;
extern uint16_t advik_global_channels;
extern uint16_t advik_global_command_linger;
extern uint16_t advik_global_volume;
extern uint16_t advik_change_order;

extern uint16_t advik_arp_tick;
extern uint16_t advik_arp_index;

// --------------------------------------------------------------------
// CHANNEL PLAYER VARIABLES
// --------------------------------------------------------------------

struct advikChannel {
	uint16_t volume;
	uint16_t pan;
	uint16_t current_freq;
	uint16_t base_freq;
	uint16_t current_note;
	uint16_t base_note;
	uint16_t instrument;
	
	uint16_t arp_offsets;
	uint16_t arp_enabled;
	
	uint16_t portamento_direction;
	uint16_t portamento_speed;
	uint16_t portamento_note_goal;
	uint16_t portamento_freq_goal;
	uint16_t previous_freq;
	
	uint16_t vib_position;
	uint16_t vib_ticks_counter;
	uint16_t vib_depth;
	uint16_t vib_speed;
	uint16_t vib_enabled;
	
	uint16_t delay_ticks_counter;
	uint16_t delay_enabled;
	uint16_t cut_delay_enabled;
	
	uint16_t timbre_goal;
	
	int16_t volume_slide_speed;
	uint16_t volume_slide_enabled;
	
	uint16_t loaded_wave;
	
	uint16_t sample_duration;
	
	uint16_t queue_note;
	uint16_t queue_instrument;
	uint16_t queue_cut;
	uint16_t queue_timbre;
	uint16_t queue_volume;
	uint16_t effect;
	uint16_t effect_param;
	
	uint16_t queue_global_volume;
	uint16_t queue_global_pan;
};

extern struct advikChannel ch[6];

extern const uint8_t * const * advik_global_current_order;
extern const uint8_t * advik_global_current_header;
extern const uint16_t * advik_current_square_instruments;
extern const uint16_t * advik_current_wave_instruments;
extern const uint16_t * const * advik_current_waveforms;
extern const uint16_t * advik_current_noise_instruments;
extern const uint8_t * const * advik_current_dma_instruments;
extern const uint16_t * advik_current_dma_durations;

extern const uint8_t * advik_ch_current_order[6];
extern const uint8_t * advik_ch_sfx_order[6];
extern uint16_t advik_ch_sfx_override[6];
extern uint16_t advik_ch_sfx_current[6];
extern uint16_t advik_ch_sfx_ticks_per_row_counter[6];
extern uint16_t advik_ch_sfx_ticks_per_row_value[6];
extern uint16_t advik_ch_sfx_command_linger[6];

extern const uint8_t * advik_ch_sfx_current_header[6];
extern const uint16_t * advik_sfx_current_square_instruments[2];
extern const uint16_t * advik_sfx_current_wave_instruments;
extern const uint16_t * const * advik_sfx_current_waveforms;
extern const uint16_t * advik_sfx_current_noise_instruments;
extern const uint8_t * const * advik_sfx_current_dma_instruments[2];
extern const uint16_t * advik_sfx_current_dma_durations[2];

typedef struct advikSongStruct {
	const uint8_t * const * const global_order;
	const uint8_t * const global_header;
	const uint16_t * const square_inst;
	const uint16_t * const wave_inst;
	const uint16_t * const * const waveforms;
	const uint16_t * const noise_inst;
	const uint8_t * const * const dma_inst;
	const uint16_t * const dma_dur;
} advikSongStruct;

typedef struct advikSFXStruct {
	const uint8_t * const sfx_order;
	const uint8_t * const sfx_header;
	const uint16_t * const square_inst;
	const uint16_t * const wave_inst;
	const uint16_t * const * const waveforms;
	const uint16_t * const noise_inst;
	const uint8_t * const * const dma_inst;
	const uint16_t * const dma_dur;
} advikSFXStruct;

// --------------------------------------------------------------------
// TONE GENERATOR
// --------------------------------------------------------------------

extern const uint16_t snd_freqs[];
extern const uint16_t dma_snd_freqs[];
extern const int16_t vib_table[];

// --------------------------------------------------------------------
// MACROS 
// --------------------------------------------------------------------

#define SWAV_LEN_MASK 0x00FF
#define SWAV_LEN_SHIFT	0
#define SWAV_LEN(n)	((n)<<SWAV_LEN_SHIFT)

#define SWAV_LEN_ON	0x4000
#define SWAV_LEN_OFF	0x0000

#define SWAV_VOL75	0x8000
#define SWAV_VOL0	0x0000
#define SWAV_VOL100	0x2000
#define SWAV_VOL50	0x4000
#define SWAV_VOL25	0x6000

#define SNOI_FREQ_MASK 0x0007
#define SNOI_FREQ_SHIFT	0
#define SNOI_FREQ(n) ((n)<<SNOI_FREQ_SHIFT)

#define SNOI_OCTAVE_MASK 0x00F0
#define SNOI_OCTAVE_SHIFT	4
#define SNOI_OCTAVE(n) ((n)<<SNOI_OCTAVE_SHIFT)

#define SNOI_POLYNOM(n) (((((n) % 4) + 4) | ((((n) - 4) >> 2) << 4)) << 7)

#define SNOI_SHORT 0x0008
#define SNOI_LONG 0x0000

#define SNOI_SHORT_PACK 0x0040
#define SNOI_LONG_PACK 0x0000

#define SNOI_UNPACK_SHIFT 3
#define SNOI_UNPACK(n) ((n)>>SNOI_UNPACK_SHIFT)

#define SNOI_EXCLUDE_PACK 0xFFDF
#define SNOI_EXCLUDE_UNPACK 0xFFF7

#endif

