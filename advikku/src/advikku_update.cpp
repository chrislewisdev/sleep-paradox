#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tonc.h>

#include "advikku_global.h"
#include "advikku_update.h"

static inline void cell_song_hw_write_ch1(const uint16_t * inst) {
	
	//channel 1
	if (ch[0].queue_note) {
		//write instrument
		if (ch[0].queue_instrument) {
			if (ch[0].queue_volume) {
				if ((ch[0].volume & 0xf0))
					REG_SND1CNT = ((inst[ch[0].instrument] & 0x00ff) | (ch[0].volume << 12)) | ((ch[0].volume & 0xf0) << 4);
				else
					REG_SND1CNT = ((inst[ch[0].instrument] & 0x0fff) | (ch[0].volume << 12));
				if (!advik_global_command_linger)
					ch[0].queue_volume = 0;
			} else {
				REG_SND1CNT = inst[ch[0].instrument];
			}
			ch[0].queue_instrument = 0;
		}
		//write note
		if (inst[ch[0].instrument] & SSQR_LEN_MASK)
			REG_SND1FREQ = SFREQ_RESET | ch[0].current_freq | SFREQ_TIMED;
		else
			REG_SND1FREQ = SFREQ_RESET | ch[0].current_freq;
		ch[0].queue_note = 0;
	} else if (ch[0].queue_cut) {
		//cut the note through the instrument
		REG_SND1CNT = 0;
		ch[0].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_SND1FREQ = ch[0].current_freq;
	}
	
	if (ch[0].queue_timbre) {
		REG_SND1CNT = ((inst[ch[0].instrument] & 0xff00) | ch[0].timbre_goal);
	}
}

static inline void cell_song_hw_write_ch2(const uint16_t * inst) {	
	//channel 2
	if (ch[1].queue_note) {
		//write instrument
		if (ch[1].queue_instrument) {
			if (ch[1].queue_volume) {
				if ((ch[1].volume & 0xf0))
					REG_SND2CNT = ((inst[ch[1].instrument] & 0x00ff) | (ch[1].volume << 12)) | ((ch[1].volume & 0xf0) << 4);
				else
					REG_SND2CNT = ((inst[ch[1].instrument] & 0x0fff) | (ch[1].volume << 12));
				if (!advik_global_command_linger)
					ch[1].queue_volume = 0;
			} else {
				REG_SND2CNT = inst[ch[1].instrument];
			}
			ch[1].queue_instrument = 0;
		}
		//write note
		if (inst[ch[1].instrument] & SSQR_LEN_MASK)
			REG_SND2FREQ = SFREQ_RESET | ch[1].current_freq | SFREQ_TIMED;
		else
			REG_SND2FREQ = SFREQ_RESET | ch[1].current_freq;
		ch[1].queue_note = 0;
	} else if (ch[1].queue_cut) {
		//cut the note through the instrument
		REG_SND2CNT = 0;
		ch[1].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_SND2FREQ = ch[1].current_freq;
	}
	
	if (ch[1].queue_timbre) {
		REG_SND2CNT = ((inst[ch[1].instrument] & 0xff00) | ch[1].timbre_goal);
	}
}
static inline void cell_song_hw_write_ch3(const uint16_t * inst, const uint16_t * const * wave) {
	//channel 3
	if (ch[2].queue_note) {
		//write instrument
		if (ch[2].queue_instrument) {
			if (ch[2].queue_volume) {
				//check volume and assign the right value
				switch(ch[2].volume & 0x0c){
					case 0:
						REG_SND3CNT = SWAV_VOL0;
						break;
					case 4:
						REG_SND3CNT = SWAV_VOL25;
						break;
					case 8:
						REG_SND3CNT = SWAV_VOL50;
						break;
					default:
						REG_SND3CNT = SWAV_VOL100;
				}
				if (!advik_global_command_linger)
					ch[2].queue_volume = 0;
			} else {
				REG_SND3CNT = SWAV_VOL100;
			}
			//copy channel 3 waveform over
			REG_SND3SEL = 0;
			memcpy((void *)REG_WAVE_RAM, wave[ch[2].instrument], 16);
			REG_SND3SEL = 0xC0;
			
			ch[2].queue_instrument = 0;
		}
		//write note
		if (inst[ch[2].instrument << 1] == SWAV_LEN_ON)
			REG_SND3FREQ = SFREQ_RESET | ch[2].current_freq | SFREQ_TIMED;
		else
			REG_SND3FREQ = SFREQ_RESET | ch[2].current_freq;
		ch[2].queue_note = 0;
	} else if (ch[2].queue_cut) {
		//cut the note through the instrument
		REG_SND3CNT = 0;
		ch[2].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_SND3FREQ = ch[2].current_freq;
	}
	
	if (ch[2].queue_timbre) {
		REG_SND3SEL = 0;
		memcpy((void *)REG_WAVE_RAM, wave[ch[2].timbre_goal], 16);
		REG_SND3SEL = 0xC0;
	}
}
static inline void cell_song_hw_write_ch4(const uint16_t * inst) {
	//channel 4
	if (ch[3].queue_note) {
		//write instrument
		if (ch[3].queue_instrument) {
			if (ch[3].queue_volume) {
				if ((ch[3].volume & 0xf0))
					REG_SND4CNT = (((inst[ch[3].instrument] & 0x00ff) & SNOI_EXCLUDE_PACK) | (ch[3].volume << 12)) | ((ch[3].volume & 0xf0) << 4);
				else
					REG_SND4CNT = (((inst[ch[3].instrument] & 0x0fff) & SNOI_EXCLUDE_PACK) | (ch[3].volume << 12));
				if (!advik_global_command_linger)
					ch[3].queue_volume = 0;
			} else {
				REG_SND4CNT = (inst[ch[3].instrument] & SNOI_EXCLUDE_PACK);
			}
			ch[3].queue_instrument = 0;
		}
		//write note
		if (inst[ch[3].instrument] & SSQR_LEN_MASK)
			REG_SND4FREQ = SFREQ_RESET | (ch[3].current_freq & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(inst[ch[3].instrument] & SNOI_SHORT_PACK)) | SFREQ_TIMED;
		else
			REG_SND4FREQ = SFREQ_RESET | (ch[3].current_freq & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(inst[ch[3].instrument] & SNOI_SHORT_PACK));
		ch[3].queue_note = 0;
	} else if (ch[3].queue_cut) {
		//cut the note through the instrument
		REG_SND4CNT = 0;
		ch[3].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_SND4FREQ = (ch[3].current_freq & SNOI_EXCLUDE_UNPACK) | (SNOI_UNPACK(inst[ch[3].instrument] & SNOI_SHORT_PACK));
	}
	
	if (ch[3].queue_timbre) {
		REG_SND4CNT = ((inst[ch[3].instrument] & 0xff00) | ch[3].timbre_goal);
	}
}
static inline void cell_song_hw_write_ch5(const uint8_t * const * inst) {
	//channel 5
	if (ch[4].queue_note) {
		//write instrument
		if (ch[4].queue_instrument) {
			if (ch[4].queue_volume) {
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfffb) | ((ch[4].volume & 1) << 2);
				if (!advik_global_command_linger)
					ch[4].queue_volume = 0;
			} else {
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfffb) | ((0x01) << 2);
			}
			REG_DMA1CNT = 0;
			//set DMA transfer to DAC 1 FIFO
			REG_DMA1SAD = (uint32_t)inst[ch[4].instrument];
			REG_DMA1DAD = (uint32_t)&REG_FIFO_A;
			REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
			ch[4].queue_instrument = 0;
		}
		//write note
		//set timer 0
		REG_TM0D = ch[4].current_freq;
		REG_TM0CNT = TM_ENABLE;
		ch[4].queue_note = 0;
	} else if (ch[4].queue_cut) {
		//cut the note through the instrument
		REG_DMA1CNT = 0;
		ch[4].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_TM0D = ch[4].current_freq;
		REG_TM0CNT = TM_ENABLE;
	}
}
static inline void cell_song_hw_write_ch6(const uint8_t * const * inst) {
	//channel 6
	if (ch[5].queue_note) {
		//write instrument
		if (ch[5].queue_instrument) {
			if (ch[5].queue_volume) {
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff7) | ((ch[5].volume & 1) << 3);
				if (!advik_global_command_linger)
					ch[5].queue_volume = 0;
			} else {
				REG_SNDDSCNT = (REG_SNDDSCNT & 0xfff7) | ((0x01) << 3);
			}
			REG_DMA2CNT = 0;
			//set DMA transfer to DAC 1 FIFO
			REG_DMA2SAD = (uint32_t)inst[ch[5].instrument];
			REG_DMA2DAD = (uint32_t)&REG_FIFO_B;
			REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA_32 | DMA_AT_REFRESH | DMA_ENABLE;
			
			ch[5].queue_instrument = 0;
		}
		//write note
		//set timer 0
		REG_TM1D = ch[5].current_freq;
		REG_TM1CNT = TM_ENABLE;
		ch[5].queue_note = 0;
	} else if (ch[5].queue_cut) {
		//cut the note through the instrument
		REG_DMA2CNT = 0;
		ch[5].queue_cut = 0;
	} else {
		//do not retrigger the note otherwise
		REG_TM1D = ch[5].current_freq;
		REG_TM1CNT = TM_ENABLE;
	}
}

void cell_song_update() {
	if (advik_ticks_per_row_counter > 0) {
		
		advik_ticks_per_row_counter--;
		advik_arp_tick++;
		advik_arp_index = advik_arp_tick % 3;
		
		//handle effects for every tick but the first
		for (uint8_t i = 0; i < advik_global_channels; i++){
			if (ch[i].delay_enabled) {
				if (ch[i].delay_ticks_counter > 0) {
					ch[i].delay_ticks_counter--;
				} else {
					if (advik_ch_current_order[i][advik_current-3] > 0x00){
						ch[i].instrument = advik_ch_current_order[i][advik_current-3] - 1;
						ch[i].queue_instrument = 1;
					}
					ch[i].base_note = advik_ch_current_order[i][advik_current-4];
					ch[i].current_note = ch[i].base_note;
					if (i < 3) {
						ch[i].base_freq = snd_freqs[ch[i].base_note];
						ch[i].current_freq = snd_freqs[ch[i].current_note];
					} else if (i >= 4) {
						ch[i].base_freq = dma_snd_freqs[ch[i].base_note];
						ch[i].current_freq = dma_snd_freqs[ch[i].current_note];
					} else {
						ch[i].base_freq = SNOI_POLYNOM(ch[i].base_note);
						ch[i].current_freq = SNOI_POLYNOM(ch[i].current_note);
					}
					ch[i].queue_note = 1;
					ch[i].delay_enabled = 0;
				}
			} else if (ch[i].portamento_direction) {
				//portamento up
				if (ch[i].portamento_direction == 1)
					ch[i].current_freq += ch[i].portamento_speed;
				//portamento down
				else if (ch[i].portamento_direction == 2)
					ch[i].current_freq -= ch[i].portamento_speed;
				//tone portamento
				else if (ch[i].portamento_direction == 3) {
					if (ch[i].portamento_freq_goal > ch[i].current_freq)
						ch[i].current_freq -= ch[i].portamento_speed;
					else if (ch[i].portamento_freq_goal < ch[i].current_freq)
						ch[i].current_freq += ch[i].portamento_speed;
				}
			} else if (ch[i].arp_enabled) {
				switch (advik_arp_index) {
					case 1:
						ch[i].current_note = ch[i].base_note + (ch[i].arp_offsets >> 4);
						break;
					case 2:
						ch[i].current_note = ch[i].base_note + (ch[i].arp_offsets & 0x0f);
						break;
					default:
						ch[i].current_note = ch[i].base_note;
				}
				if (i < 3) {
					ch[i].base_freq = snd_freqs[ch[i].base_note];
					ch[i].current_freq = snd_freqs[ch[i].current_note];
				} else if (i >= 4) {
					ch[i].base_freq = dma_snd_freqs[ch[i].base_note];
					ch[i].current_freq = dma_snd_freqs[ch[i].current_note];
				} else {
					ch[i].base_freq = SNOI_POLYNOM(snd_freqs[ch[i].base_note]);
					ch[i].current_freq = SNOI_POLYNOM(snd_freqs[ch[i].current_note]);
				}
			} else if (ch[i].cut_delay_enabled) {
				if (ch[i].delay_ticks_counter > 0) {
					ch[i].delay_ticks_counter--;
				} else {
					ch[i].queue_cut = 1;
					ch[i].cut_delay_enabled = 0;
				}
			} else if (ch[i].vib_enabled) {
				ch[i].vib_ticks_counter += ch[i].vib_speed;
				ch[i].vib_position = ch[i].vib_ticks_counter & 63;
				ch[i].current_freq = (ch[i].base_freq - ((vib_table[ch[i].vib_position] * (ch[i].vib_depth)) >> 5));
			} else if (ch[i].volume_slide_enabled) {
				//if volume is greater than 0
				if ((ch[i].volume & 0x0f)) {
					//clamp it to 0 if speed is too fast and negative
					if (ch[i].volume_slide_speed >= (ch[i].volume & 0xfff0))
						ch[i].volume = 0;
					//or clamp it to 15 if speed is too fast and positive
					else if (ch[i].volume_slide_speed <= -(ch[i].volume & 0xfff0))
						ch[i].volume = (ch[i].volume & 0xfff0) | 0x0F;
					//or decrease the volume by the slide speed
					else
						ch[i].volume -= ch[i].volume_slide_speed;
					ch[i].queue_volume = 1;
				}
			}
		}
		
	} else {
		if (!advik_global_command_linger){
			for (uint8_t i = 0; i < advik_global_channels; i++) {
				ch[i].arp_enabled = 0;
				ch[i].portamento_direction = 0;
				ch[i].vib_enabled = 0;
				ch[i].vib_ticks_counter = 0;
				ch[i].current_note = ch[i].base_note;
				ch[i].volume = 0x0f;
			}
		}
		
		for (uint8_t i = 0; i < advik_global_channels; i++) {
			if (!advik_ch_sfx_command_linger[i] && !advik_ch_sfx_override[i]) {
				ch[i].arp_enabled = 0;
				ch[i].portamento_direction = 0;
				ch[i].vib_enabled = 0;
				ch[i].vib_ticks_counter = 0;
				ch[i].current_note = ch[i].base_note;
				ch[i].volume = 0x0f;
			}
		}
		
		//change order when queued
		if (advik_change_order) {
			advik_change_order = 0;
			advik_current = advik_future;
			for (uint8_t i = 0; i < advik_global_channels; i++){
				advik_ch_current_order[i] = advik_global_current_order[advik_global_order_number+i];
			}
		}
		
		//if end of order is reached, loop
		if (advik_ch_current_order[0][advik_current] == 0xff) {
			advik_current = 0;
			if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
				advik_global_order_number += advik_global_channels;
			else
				advik_global_order_number = (advik_loop_point * advik_global_channels);
			
			for (uint8_t i = 0; i < advik_global_channels; i++){
				advik_ch_current_order[i] = advik_global_current_order[advik_global_order_number+i];
			}
		}
		
		//for each channel, queue a note and instrument and effect when needed
		for (uint8_t i = 0; i < advik_global_channels; i++) {
			if(!advik_ch_sfx_override[i]){
				ch[i].effect = advik_ch_current_order[i][advik_current+2];
				ch[i].effect_param = advik_ch_current_order[i][advik_current+3];
				
				switch (ch[i].effect) {
					//if arpeggio
					case 0x00:
						if (ch[i].effect_param > 0) {
							ch[i].arp_offsets = ch[i].effect_param;
							ch[i].arp_enabled = 1;
						} else if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].arp_enabled = 0;
							ch[i].current_note = ch[i].base_note;
						}
						break;
					//if portamento up
					case 0x01:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 1;
							ch[i].portamento_speed = ch[i].effect_param;
						} else if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if portamento down
					case 0x02:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 2;
							ch[i].portamento_speed = ch[i].effect_param;
						} else if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if tone portamento
					case 0x03:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 3;
							if (advik_ch_current_order[i][advik_current] < 0xf0) {
								ch[i].portamento_note_goal = advik_ch_current_order[i][advik_current];
								if (i < 3)
									ch[i].portamento_freq_goal = snd_freqs[advik_ch_current_order[i][advik_current]];
								else if (i >= 4)
									ch[i].portamento_freq_goal = dma_snd_freqs[advik_ch_current_order[i][advik_current]];
							}
						} else if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if vibrato
					case 0x04:
						ch[i].vib_depth = ch[i].effect_param & 0x0f;
						ch[i].vib_speed = ch[i].effect_param & 0xf0;
						ch[i].vib_enabled = 1;
						if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].vib_enabled = 0;
							ch[i].current_note = ch[i].base_note;
						}
						break;
					//if set master volume
					case 0x05:
						ch[i].queue_global_volume = 1;
						if (i < 4)
							advik_global_volume = ch[i].effect_param;
						break;
					//if note delay
					case 0x07:
						ch[i].delay_enabled = 1;
						ch[i].delay_ticks_counter = ch[i].effect_param - 1;
						break;
					//if set global panning
					case 0x08:
						ch[i].queue_global_pan = 1;
						break;
					//if change timbre
					case 0x09:
						ch[i].timbre_goal = ch[i].effect_param;
						ch[i].queue_timbre = 1;
						break;
					//if volume slide
					case 0x0a:
						if (ch[i].effect_param == 0 && advik_global_command_linger) {
							ch[i].volume_slide_enabled = 0;
						} else {
							if ((ch[i].effect_param & 0xf0) > 0)
								ch[i].volume_slide_speed = -ch[i].effect_param;
							else if ((ch[i].effect_param & 0x0f) > 0)
								ch[i].volume_slide_speed = ch[i].effect_param;
							ch[i].volume_slide_enabled = 1;
						}
						break;
					//if change order
					case 0x0b:
						advik_global_order_number = (ch[i].effect_param * advik_global_channels);
						advik_future = 0;
						advik_change_order = 1;
						break;
					//if set volume
					case 0x0c:
						if (ch[i].effect_param == 0) {
							ch[i].queue_cut = 1;
						} else {
							ch[i].queue_volume = 1;
							ch[i].volume = ch[i].effect_param;
						}
						break;
					//if pattern break
					case 0x0d:
						if (advik_global_order_number < ((advik_global_order_length - 1) * advik_global_channels))
							advik_global_order_number += advik_global_channels;
						else
							advik_global_order_number = (advik_loop_point * advik_global_channels);
						
						advik_future = ch[i].effect_param;
						advik_change_order = 1;
						break;
					//if note cut
					case 0x0e:
						ch[i].cut_delay_enabled = 1;
						ch[i].delay_ticks_counter = ch[i].effect_param - 1;
						break;
					//if set tempo
					case 0x0f:
						advik_ticks_per_row_value = ch[i].effect_param - 1;
						break;
					//if set furnace panning
					case 0x80:
						ch[i].pan = ch[i].effect_param;
				}
				
				if (advik_ch_current_order[i][advik_current] < 0xf8 && !ch[i].delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_current_order[i][advik_current+1] > 0x00){
						ch[i].instrument = advik_ch_current_order[i][advik_current+1] - 1;
						ch[i].queue_instrument = 1;
					}
					
					ch[i].base_note = advik_ch_current_order[i][advik_current];
					ch[i].current_note = ch[i].base_note;
					if (i < 3) {
						ch[i].base_freq = snd_freqs[ch[i].base_note];
						ch[i].current_freq = snd_freqs[ch[i].current_note];
					} else if (i >= 4) {
						ch[i].base_freq = dma_snd_freqs[ch[i].base_note];
						ch[i].current_freq = dma_snd_freqs[ch[i].current_note];
						ch[i].sample_duration = advik_current_dma_durations[ch[i].instrument];
					} else {
						ch[i].base_freq = SNOI_POLYNOM(ch[i].base_note);
						ch[i].current_freq = SNOI_POLYNOM(ch[i].current_note);
					}
					ch[i].queue_note = 1;
				}
			} else {
				ch[i].effect = advik_ch_sfx_order[i][advik_ch_sfx_current[i]+2];
				ch[i].effect_param = advik_ch_sfx_order[i][advik_ch_sfx_current[i]+3];
				
				switch (ch[i].effect) {
					//if arpeggio
					case 0x00:
						if (ch[i].effect_param > 0) {
							ch[i].arp_offsets = ch[i].effect_param;
							ch[i].arp_enabled = 1;
						} else if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].arp_enabled = 0;
							ch[i].current_note = ch[i].base_note;
						}
						break;
					//if portamento up
					case 0x01:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 1;
							ch[i].portamento_speed = ch[i].effect_param;
						} else if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if portamento down
					case 0x02:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 2;
							ch[i].portamento_speed = ch[i].effect_param;
						} else if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if tone portamento
					case 0x03:
						if (ch[i].effect_param > 0) {
							ch[i].portamento_direction = 3;
							if (advik_ch_current_order[i][advik_current] < 0xf0) {
								ch[i].portamento_note_goal = advik_ch_sfx_order[i][advik_ch_sfx_current[i]];
								if (i < 3)
									ch[i].portamento_freq_goal = snd_freqs[advik_ch_sfx_order[i][advik_ch_sfx_current[i]]];
								else if (i >= 4)
									ch[i].portamento_freq_goal = dma_snd_freqs[advik_ch_sfx_order[i][advik_ch_sfx_current[i]]];
							}
						} else if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].portamento_direction = 0;
						}
						break;
					//if vibrato
					case 0x04:
						ch[i].vib_depth = ch[i].effect_param & 0x0f;
						ch[i].vib_speed = ch[i].effect_param & 0xf0;
						ch[i].vib_enabled = 1;
						if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].vib_enabled = 0;
							ch[i].current_note = ch[i].base_note;
						}
						break;
					//if set master volume
					case 0x05:
						ch[i].queue_global_volume = 1;
						if (i < 4)
							advik_global_volume = ch[i].effect_param;
						break;
					//if note delay
					case 0x07:
						ch[i].delay_enabled = 1;
						ch[i].delay_ticks_counter = ch[i].effect_param - 1;
						break;
					//if set global panning
					case 0x08:
						ch[i].queue_global_pan = 1;
						break;
					//if change timbre
					case 0x09:
						ch[i].timbre_goal = ch[i].effect_param;
						ch[i].queue_timbre = 1;
						break;
					//if volume slide
					case 0x0a:
						if (ch[i].effect_param == 0 && advik_ch_sfx_command_linger[i]) {
							ch[i].volume_slide_enabled = 0;
						} else {
							if ((ch[i].effect_param & 0xf0) > 0)
								ch[i].volume_slide_speed = -ch[i].effect_param;
							else if ((ch[i].effect_param & 0x0f) > 0)
								ch[i].volume_slide_speed = ch[i].effect_param;
							ch[i].volume_slide_enabled = 1;
						}
						break;
					//if set volume
					case 0x0c:
						ch[i].queue_volume = 1;
						ch[i].volume = ch[i].effect_param;
						break;
					//if pattern break
					case 0x0d:
						advik_ch_sfx_override[i] = 0;
						ch[i].queue_cut = 1;
						break;
					//if note cut
					case 0x0e:
						ch[i].cut_delay_enabled = 1;
						ch[i].delay_ticks_counter = ch[i].effect_param - 1;
						break;
					//if set tempo
					case 0x0f:
						advik_ticks_per_row_value = ch[i].effect_param - 1;
						break;
					//if set furnace panning
					case 0x80:
						ch[i].pan = ch[i].effect_param;
				}
				if (advik_ch_sfx_order[i][advik_ch_sfx_current[i]] < 0xf8 && !ch[i].delay_enabled) {
					//if instrument isn't 0, retrigger note
					if (advik_ch_sfx_order[i][advik_ch_sfx_current[i]+1] > 0x00){
						ch[i].instrument = advik_ch_sfx_order[i][advik_ch_sfx_current[i]+1] - 1;
						ch[i].queue_instrument = 1;
					}
					
					ch[i].base_note = advik_ch_sfx_order[i][advik_ch_sfx_current[i]];
					ch[i].current_note = ch[i].base_note;
					if (i < 3) {
						ch[i].base_freq = snd_freqs[ch[i].base_note];
						ch[i].current_freq = snd_freqs[ch[i].current_note];
					} else if (i >= 4) {
						ch[i].base_freq = dma_snd_freqs[ch[i].base_note];
						ch[i].current_freq = dma_snd_freqs[ch[i].current_note];
						ch[i].sample_duration = advik_sfx_current_dma_durations[i - 4][ch[i].instrument];
					} else {
						ch[i].base_freq = SNOI_POLYNOM(ch[i].base_note);
						ch[i].current_freq = SNOI_POLYNOM(ch[i].current_note);
					}
					ch[i].queue_note = 1;
				}
				advik_ch_sfx_current[i] += 4;
				advik_ch_sfx_ticks_per_row_counter[i] = advik_ch_sfx_ticks_per_row_value[i];
				
				//if end of order is reached, don't loop
				if (advik_ch_sfx_order[i][advik_ch_sfx_current[i]] == 0xff) {
					advik_ch_sfx_override[i] = 0;
					ch[i].queue_cut = 1;
				}
			}
		}
		
		advik_current += 4;
		advik_ticks_per_row_counter = advik_ticks_per_row_value;
		advik_arp_tick = 0;
	}
	
	if (ch[4].sample_duration){
		ch[4].sample_duration--;
	} else {
		ch[4].queue_cut = 1;
	}
	if (ch[5].sample_duration){
		ch[5].sample_duration--;
	} else {
		ch[5].queue_cut = 1;
	}
	
	//global
	REG_SNDDMGCNT = (REG_SNDDMGCNT & 0xff00) | advik_global_volume;
	
	if (!advik_ch_sfx_override[0])
		cell_song_hw_write_ch1(advik_current_square_instruments);
	else
		cell_song_hw_write_ch1(advik_sfx_current_square_instruments[0]);
	if (!advik_ch_sfx_override[1])
		cell_song_hw_write_ch2(advik_current_square_instruments);
	else
		cell_song_hw_write_ch2(advik_sfx_current_square_instruments[1]);
	if (!advik_ch_sfx_override[2])
		cell_song_hw_write_ch3(advik_current_wave_instruments, advik_current_waveforms);
	else
		cell_song_hw_write_ch3(advik_sfx_current_wave_instruments, advik_sfx_current_waveforms);
	if (!advik_ch_sfx_override[3])
		cell_song_hw_write_ch4(advik_current_noise_instruments);
	else
		cell_song_hw_write_ch4(advik_sfx_current_noise_instruments);
	if (!advik_ch_sfx_override[4])
		cell_song_hw_write_ch5(advik_current_dma_instruments);
	else
		cell_song_hw_write_ch5(advik_sfx_current_dma_instruments[0]);
	if (!advik_ch_sfx_override[5])
		cell_song_hw_write_ch6(advik_current_dma_instruments);
	else
		cell_song_hw_write_ch6(advik_sfx_current_dma_instruments[1]);
}