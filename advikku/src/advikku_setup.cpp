#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>

#include "advikku_global.h"
#include "advikku_setup.h"

void cell_song_setup(advikSongStruct setsong) {
	
	advik_global_current_order = setsong.global_order;
	advik_global_current_header = setsong.global_header;
	advik_current_square_instruments = setsong.square_inst;
	advik_current_wave_instruments = setsong.wave_inst;
	advik_current_waveforms = setsong.waveforms;
	advik_current_noise_instruments = setsong.noise_inst;
	advik_current_dma_instruments = setsong.dma_inst;
	advik_current_dma_durations = setsong.dma_dur;
	
	advik_ticks_per_row_value = advik_global_current_header[0] - 1;
	advik_start = 0;
	advik_current = 0;
	advik_global_channels = advik_global_current_header[2];
	advik_global_order_length = advik_global_current_header[3];
	advik_loop_point = advik_global_current_header[4];
	advik_global_command_linger = advik_global_current_header[5];
	
	for (uint8_t i = 0; i < advik_global_channels; i++){
		advik_ch_current_order[i] = advik_global_current_order[i];
	}
}

void cell_sfx_setup(advikSFXStruct setsfx, uint16_t sfx_chan) {
	
	advik_ch_sfx_current_header[sfx_chan] = setsfx.sfx_header;
	if (sfx_chan <= 1) {
		advik_sfx_current_square_instruments[sfx_chan] = setsfx.square_inst;
	} else if (sfx_chan == 2) {
		advik_sfx_current_wave_instruments = setsfx.wave_inst;
		advik_sfx_current_waveforms = setsfx.waveforms;
	} else if (sfx_chan == 3) {
		advik_sfx_current_noise_instruments = setsfx.noise_inst;
	} else if (sfx_chan > 3) {
		advik_sfx_current_dma_instruments[sfx_chan-4] = setsfx.dma_inst;
		advik_sfx_current_dma_durations[sfx_chan-4] = setsfx.dma_dur;
	}
	advik_ch_sfx_ticks_per_row_value[sfx_chan] = advik_ch_sfx_current_header[sfx_chan][0] - 1;
	advik_ch_sfx_current[sfx_chan] = 0;
	
	advik_ch_sfx_command_linger[sfx_chan] = advik_ch_sfx_current_header[sfx_chan][5];
	
	advik_ch_sfx_order[sfx_chan] = setsfx.sfx_order;
	
	advik_ch_sfx_override[sfx_chan] = 1;
}
