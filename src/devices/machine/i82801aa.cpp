// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
#include "emu.h"
#include "i82801aa.h"
#include "bus/pc_kbd/keyboards.h"
#include "speaker.h"

DEFINE_DEVICE_TYPE(I82801AA_LPC,      i82801aa_lpc_device,      "i82801aa_lpc",      "i82801AA southbridge ISA/LPC bridge")
DEFINE_DEVICE_TYPE(I82801AA_IDE, 	  i82801aa_ide_device, 		"i82801aa_ide", 	 "Intel i82801AA southbridge IDE interface")


void i82801aa_lpc_device::config_map(address_map &map)
{
	pci_device::config_map(map);
	map(0x40, 0x43).rw(FUNC(i82801aa_lpc_device::pmbase_r), FUNC(i82801aa_lpc_device::pmbase_w));
	map(0x44, 0x44).rw(FUNC(i82801aa_lpc_device::acpi_cntl_r), FUNC(i82801aa_lpc_device::acpi_cntl_w));
	map(0x4e, 0x4f).rw(FUNC(i82801aa_lpc_device::bios_cntl_r), FUNC(i82801aa_lpc_device::bios_cntl_w));
	map(0x54, 0x54).rw(FUNC(i82801aa_lpc_device::tco_cntl_r), FUNC(i82801aa_lpc_device::tco_cntl_w));
	map(0x58, 0x5b).rw(FUNC(i82801aa_lpc_device::gpio_base_r), FUNC(i82801aa_lpc_device::gpio_base_w));
	map(0x5c, 0x5c).rw(FUNC(i82801aa_lpc_device::gpio_cntl_r), FUNC(i82801aa_lpc_device::gpio_cntl_w));
	map(0x60, 0x63).rw(FUNC(i82801aa_lpc_device::pirq_rout_r), FUNC(i82801aa_lpc_device::pirq_rout_w));
	map(0x64, 0x64).rw(FUNC(i82801aa_lpc_device::serirq_cntl_r), FUNC(i82801aa_lpc_device::serirq_cntl_w));
	map(0x68, 0x6b).rw(FUNC(i82801aa_lpc_device::pirq2_rout_r), FUNC(i82801aa_lpc_device::pirq2_rout_w));
	map(0x88, 0x88).rw(FUNC(i82801aa_lpc_device::d31_err_cfg_r), FUNC(i82801aa_lpc_device::d31_err_cfg_w));
	map(0x8a, 0x8a).rw(FUNC(i82801aa_lpc_device::d31_err_sts_r), FUNC(i82801aa_lpc_device::d31_err_sts_w));
	map(0x90, 0x91).rw(FUNC(i82801aa_lpc_device::pci_dma_cfg_r), FUNC(i82801aa_lpc_device::pci_dma_cfg_w));
	map(0xa0, 0xa1).rw(FUNC(i82801aa_lpc_device::gen_pmcon_1_r), FUNC(i82801aa_lpc_device::gen_pmcon_1_w));
	map(0xa2, 0xa2).rw(FUNC(i82801aa_lpc_device::gen_pmcon_2_r), FUNC(i82801aa_lpc_device::gen_pmcon_2_w));
	map(0xa4, 0xa4).rw(FUNC(i82801aa_lpc_device::gen_pmcon_3_r), FUNC(i82801aa_lpc_device::gen_pmcon_3_w));
	map(0xac, 0xaf).rw(FUNC(i82801aa_lpc_device::rst_cnt2_r), FUNC(i82801aa_lpc_device::rst_cnt2_w));
	map(0xb2, 0xb2).rw(FUNC(i82801aa_lpc_device::apm_cnt_r), FUNC(i82801aa_lpc_device::apm_cnt_w));
	map(0xb3, 0xb3).rw(FUNC(i82801aa_lpc_device::apm_sts_r), FUNC(i82801aa_lpc_device::apm_sts_w));
	map(0xb8, 0xbb).rw(FUNC(i82801aa_lpc_device::gpi_rout_r), FUNC(i82801aa_lpc_device::gpi_rout_w));
	map(0xc0, 0xc0).rw(FUNC(i82801aa_lpc_device::mon_fwd_en_r), FUNC(i82801aa_lpc_device::mon_fwd_en_w));
	map(0xc4, 0xcb).rw(FUNC(i82801aa_lpc_device::mon_trp_rng_r), FUNC(i82801aa_lpc_device::mon_trp_rng_w));
	map(0xcc, 0xcd).rw(FUNC(i82801aa_lpc_device::mon_trp_msk_r), FUNC(i82801aa_lpc_device::mon_trp_msk_w));
	map(0xd0, 0xd3).rw(FUNC(i82801aa_lpc_device::gen_cntl_r), FUNC(i82801aa_lpc_device::gen_cntl_w));
	map(0xd4, 0xd4).rw(FUNC(i82801aa_lpc_device::gen_sta_r), FUNC(i82801aa_lpc_device::gen_sta_w));
	map(0xd5, 0xd5).rw(FUNC(i82801aa_lpc_device::back_cntl_r), FUNC(i82801aa_lpc_device::back_cntl_w));
	map(0xd8, 0xd8).rw(FUNC(i82801aa_lpc_device::rtc_conf_r), FUNC(i82801aa_lpc_device::rtc_conf_w));
	map(0xe0, 0xe0).rw(FUNC(i82801aa_lpc_device::lpc_if_com_range_r), FUNC(i82801aa_lpc_device::lpc_if_com_range_w));
	map(0xe1, 0xe1).rw(FUNC(i82801aa_lpc_device::lpc_if_fdd_lpt_range_r), FUNC(i82801aa_lpc_device::lpc_if_fdd_lpt_range_w));
	map(0xe2, 0xe2).rw(FUNC(i82801aa_lpc_device::lpc_if_sound_range_r), FUNC(i82801aa_lpc_device::lpc_if_sound_range_w));
	map(0xe3, 0xe3).rw(FUNC(i82801aa_lpc_device::fwh_dec_en1_r), FUNC(i82801aa_lpc_device::fwh_dec_en1_w));
	map(0xe4, 0xe5).rw(FUNC(i82801aa_lpc_device::gen1_dec_r), FUNC(i82801aa_lpc_device::gen1_dec_w));
	map(0xe6, 0xe7).rw(FUNC(i82801aa_lpc_device::lpc_en_r), FUNC(i82801aa_lpc_device::lpc_en_w));
	map(0xe8, 0xeb).rw(FUNC(i82801aa_lpc_device::fwh_sel1_r), FUNC(i82801aa_lpc_device::fwh_sel1_w));
	map(0xec, 0xed).rw(FUNC(i82801aa_lpc_device::gen2_dec_r), FUNC(i82801aa_lpc_device::gen2_dec_w));
	map(0xee, 0xef).rw(FUNC(i82801aa_lpc_device::fwh_sel2_r), FUNC(i82801aa_lpc_device::fwh_sel2_w));
	map(0xf0, 0xf0).rw(FUNC(i82801aa_lpc_device::fwh_dec_en2_r), FUNC(i82801aa_lpc_device::fwh_dec_en2_w));
	map(0xf2, 0xf3).rw(FUNC(i82801aa_lpc_device::func_dis_r), FUNC(i82801aa_lpc_device::func_dis_w));
	map(0xf4, 0xf7).rw(FUNC(i82801aa_lpc_device::etr1_r), FUNC(i82801aa_lpc_device::etr1_w));
	map(0xf8, 0xfb).r(FUNC(i82801aa_lpc_device::mfid_r));
	map(0xfc, 0xff).rw(FUNC(i82801aa_lpc_device::unk_fc_r), FUNC(i82801aa_lpc_device::unk_fc_w));
}

void i82801aa_lpc_device::internal_io_map(address_map &map)
{
	if(lpc_en & 0x2000) {
		map(0x004e, 0x004e).rw(FUNC(i82801aa_lpc_device::siu_config_port_r), FUNC(i82801aa_lpc_device::siu_config_port_w));
		map(0x004f, 0x004f).rw(FUNC(i82801aa_lpc_device::siu_data_port_r), FUNC(i82801aa_lpc_device::siu_data_port_w));
	}

	map(0x0061, 0x0061).rw(FUNC(i82801aa_lpc_device::nmi_sc_r), FUNC(i82801aa_lpc_device::nmi_sc_w));

	map(0x0080, 0x0080).w(FUNC(i82801aa_lpc_device::nop_w)); // POST/non-existing, used for delays by the bios/os
	map(0x00ed, 0x00ed).w(FUNC(i82801aa_lpc_device::nop_w)); // Non-existing, used for delays by the bios/os
}


i82801aa_lpc_device::i82801aa_lpc_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: pci_device(mconfig, I82801AA_LPC, tag, owner, clock)
	, m_maincpu(*this, finder_base::DUMMY_TAG)
	, acpi(*this, "acpi")
	, rtc (*this, "rtc")
	, m_pic_master(*this, "pic_master")
	, m_pic_slave(*this, "pic_slave")
	, pit (*this, "pit")
	, m_keybc(*this, "keybc")
	, m_speaker(*this, "speaker")
	, m_ps2_con(*this, "ps2_con")
	, m_aux_con(*this, "aux_con")
	, m_region(*this, DEVICE_SELF)
{
	set_ids(0x80862418, 0x02, 0x060100, 0x00000000);
}

void i82801aa_lpc_device::device_start()
{
	pci_device::device_start();
}

void i82801aa_lpc_device::device_reset()
{
	pci_device::device_reset();
	tco_cntl = 0x00;
	serirq_cntl = 0x10;
	memset(pirq_rout, 0x80, sizeof(pirq_rout));
	d31_err_cfg = 0x00;
	d31_err_sts = 0x00;
	pci_dma_cfg = 0x0000;
	func_dis = 0x0080;
	etr1 = 0x00000000;
	siu_config_port = 0;
	siu_config_state = 0;
	gen_pmcon_1 = 0;
	gen_pmcon_2 = 0;
	gen_pmcon_3 = 0;
	rst_cnt2 = 0;
	apm_cnt = 0;
	apm_sts = 0;
	gpi_rout = 0;
	mon_fwd_en = 0;
	memset(mon_trp_rng, 0, sizeof(mon_trp_rng));
	mon_trp_msk = 0;
	nmi_sc = 0;
	gen_sta = 0x00;
	command = 0x0001;
	status = 0x0080;
}

void i82801aa_lpc_device::cpu_a20_w(int state)
{
	// TODO: confirm "A20M# being always high"
//  if (BIT(m_init_reg, 1))
//      state = ASSERT_LINE;
	m_maincpu->set_input_line(INPUT_LINE_A20, state);
}

void i82801aa_lpc_device::cpu_reset_w(int state)
{
	// TODO: masked via INIT $46 bit 0
	m_maincpu->set_input_line(INPUT_LINE_RESET, state);
}

void i82801aa_lpc_device::device_add_mconfig(machine_config &config)
{
	// Confirmed 82C59s
	PIC8259(config, m_pic_master, 0);
	m_pic_master->out_int_callback().set_inputline(m_maincpu, 0);
	m_pic_master->in_sp_callback().set_constant(1);
	m_pic_master->read_slave_ack_callback().set(
		[this](offs_t offset) -> u8
		{
			if (offset == 2)
				return m_pic_slave->acknowledge();

			return 0;
		});

	PIC8259(config, m_pic_slave, 0);
	m_pic_slave->out_int_callback().set(m_pic_master, FUNC(pic8259_device::ir2_w));
	m_pic_slave->in_sp_callback().set_constant(0);

	PC_KBDC(config, m_ps2_con, pc_at_keyboards, STR_KBD_MICROSOFT_NATURAL);
	m_ps2_con->out_clock_cb().set(m_keybc, FUNC(ps2_keyboard_controller_device::kbd_clk_w));
	m_ps2_con->out_data_cb().set(m_keybc, FUNC(ps2_keyboard_controller_device::kbd_data_w));

	PC_KBDC(config, m_aux_con, ps2_mice, STR_HLE_PS2_MOUSE);
	m_aux_con->out_clock_cb().set(m_keybc, FUNC(ps2_keyboard_controller_device::aux_clk_w));
	m_aux_con->out_data_cb().set(m_keybc, FUNC(ps2_keyboard_controller_device::aux_data_w));

	// TODO: selectable between PCI clock / 4 (33 MHz) or 7.159 MHz, via reg $47 bit 5
	PS2_KEYBOARD_CONTROLLER(config, m_keybc, DERIVED_CLOCK(1, 4));
	// TODO: default ibm BIOS doesn't cope with this too well
	m_keybc->set_default_bios_tag("ibm");
	m_keybc->hot_res().set(FUNC(i82801aa_lpc_device::cpu_reset_w));
	m_keybc->gate_a20().set(FUNC(i82801aa_lpc_device::cpu_a20_w));
	m_keybc->kbd_irq().set(m_pic_master, FUNC(pic8259_device::ir1_w));
	m_keybc->kbd_clk().set(m_ps2_con, FUNC(pc_kbdc_device::clock_write_from_mb));
	m_keybc->kbd_data().set(m_ps2_con, FUNC(pc_kbdc_device::data_write_from_mb));
	m_keybc->aux_irq().set(m_pic_slave, FUNC(pic8259_device::ir4_w));
	m_keybc->aux_clk().set(m_aux_con, FUNC(pc_kbdc_device::clock_write_from_mb));
	m_keybc->aux_data().set(m_aux_con, FUNC(pc_kbdc_device::data_write_from_mb));

	/* sound hardware */
	SPEAKER(config, "mono").front_center();
	SPEAKER_SOUND(config, m_speaker).add_route(ALL_OUTPUTS, "mono", 0.50);
}

void i82801aa_lpc_device::reset_all_mappings()
{
	pci_device::reset_all_mappings();

	pmbase = 0;
	acpi_cntl = 0;
	gpio_base = 0;
	gpio_cntl = 0x00;
	back_cntl = 0x0f;
	lpc_if_com_range = 0x00;
	lpc_if_fdd_lpt_range = 0x00;
	lpc_if_sound_range = 0x00;
	fwh_dec_en1 = 0xff;
	fwh_dec_en2 = 0x0f;
	gen1_dec = 0x0000;
	lpc_en = 0x0000;
	fwh_sel1 = 0x00112233;
	gen_cntl = 0x00000080;
	rtc_conf = 0x00;
}

#if 0
void i82801aa_lpc_device::iochck_w(int state)
{
//  if (!state && !m_channel_check && m_nmi_enabled)
	if (!state && !m_channel_check)
		m_maincpu->set_input_line(INPUT_LINE_NMI, ASSERT_LINE);
}
#endif

uint32_t i82801aa_lpc_device::pmbase_r()
{
	return pmbase | 1;
}

void i82801aa_lpc_device::pmbase_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&pmbase);
	pmbase &= 0x0000ff80;
	logerror("%s: pmbase = %08x\n", tag(), pmbase);
	remap_cb();
}

uint8_t i82801aa_lpc_device::acpi_cntl_r()
{
	return acpi_cntl;
}

void i82801aa_lpc_device::acpi_cntl_w(uint8_t data)
{
	acpi_cntl = data;
	logerror("%s: acpi_cntl = %08x\n", tag(), acpi_cntl);
	remap_cb();
}

uint16_t i82801aa_lpc_device::bios_cntl_r()
{
	return pmbase | 1;
}

void i82801aa_lpc_device::bios_cntl_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&bios_cntl);
	logerror("%s: bios_cntl = %08x\n", tag(), bios_cntl);
	remap_cb();
}

uint8_t i82801aa_lpc_device::tco_cntl_r()
{
	return tco_cntl;
}

void i82801aa_lpc_device::tco_cntl_w(uint8_t data)
{
	tco_cntl = data;
	logerror("%s: tco_cntl = %02x\n", tag(), tco_cntl);
}

uint32_t i82801aa_lpc_device::gpio_base_r()
{
	return gpio_base | 1;
}

void i82801aa_lpc_device::gpio_base_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&gpio_base);
	gpio_base &= 0x0000ffc0;
	logerror("%s: gpio_base = %08x\n", tag(), gpio_base);
	remap_cb();
}

uint8_t i82801aa_lpc_device::gpio_cntl_r()
{
	return gpio_cntl;
}

void i82801aa_lpc_device::gpio_cntl_w(uint8_t data)
{
	gpio_cntl = data;
	logerror("%s: gpio_cntl = %02x\n", tag(), gpio_cntl);
	remap_cb();
}

uint8_t i82801aa_lpc_device::pirq_rout_r(offs_t offset)
{
	return pirq_rout[offset];
}

void i82801aa_lpc_device::pirq_rout_w(offs_t offset, uint8_t data)
{
	pirq_rout[offset] = data;
	logerror("%s: pirq_rout[%d] = %02x\n", tag(), offset, pirq_rout[offset]);
}

uint8_t i82801aa_lpc_device::serirq_cntl_r()
{
	return serirq_cntl;
}

void i82801aa_lpc_device::serirq_cntl_w(uint8_t data)
{
	serirq_cntl = data;
	logerror("%s: serirq_cntl = %02x\n", tag(), serirq_cntl);
}

uint8_t i82801aa_lpc_device::pirq2_rout_r(offs_t offset)
{
	return pirq_rout_r(offset+4);
}

void i82801aa_lpc_device::pirq2_rout_w(offs_t offset, uint8_t data)
{
	pirq_rout_w(offset+4, data);
}

uint8_t i82801aa_lpc_device::d31_err_cfg_r()
{
	return d31_err_cfg;
}

void i82801aa_lpc_device::d31_err_cfg_w(uint8_t data)
{
	d31_err_cfg = data;
	logerror("%s: d31_err_cfg = %02x\n", tag(), d31_err_cfg);
}

uint8_t i82801aa_lpc_device::d31_err_sts_r()
{
	return d31_err_sts;
}

void i82801aa_lpc_device::d31_err_sts_w(uint8_t data)
{
	d31_err_sts &= ~data;
	logerror("%s: d31_err_sts = %02x\n", tag(), d31_err_sts);
}

uint16_t i82801aa_lpc_device::pci_dma_cfg_r()
{
	return pci_dma_cfg;
}

void i82801aa_lpc_device::pci_dma_cfg_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&pci_dma_cfg);
	logerror("%s: pci_dma_cfg = %04x\n", tag(), pci_dma_cfg);
}

uint16_t i82801aa_lpc_device::gen_pmcon_1_r()
{
	return gen_pmcon_1;
}

void i82801aa_lpc_device::gen_pmcon_1_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&gen_pmcon_1);
	logerror("%s: gen_pmcon_1 = %04x\n", tag(), gen_pmcon_1);
}

uint8_t i82801aa_lpc_device::gen_pmcon_2_r()
{
	return gen_pmcon_2;
}

void i82801aa_lpc_device::gen_pmcon_2_w(uint8_t data)
{
	gen_pmcon_2 = data;
	logerror("%s: gen_pmcon_2 = %02x\n", tag(), gen_pmcon_2);
}

uint8_t i82801aa_lpc_device::gen_pmcon_3_r()
{
	return gen_pmcon_3;
}

void i82801aa_lpc_device::gen_pmcon_3_w(uint8_t data)
{
	gen_pmcon_3 = data;
	logerror("%s: gen_pmcon_3 = %02x\n", tag(), gen_pmcon_3);
}

uint32_t i82801aa_lpc_device::rst_cnt2_r()
{
	return rst_cnt2;
}

void i82801aa_lpc_device::rst_cnt2_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&rst_cnt2);
	logerror("%s: rst_cnt2 = %08x\n", tag(), rst_cnt2);
}

uint8_t i82801aa_lpc_device::apm_cnt_r()
{
	return apm_cnt;
}

void i82801aa_lpc_device::apm_cnt_w(uint8_t data)
{
	apm_cnt = data;
	logerror("%s: apm_cnt = %02x\n", tag(), apm_cnt);
}

uint8_t i82801aa_lpc_device::apm_sts_r()
{
	return apm_sts;
}

void i82801aa_lpc_device::apm_sts_w(uint8_t data)
{
	apm_sts = data;
	logerror("%s: apm_sts = %02x\n", tag(), apm_sts);
}

uint32_t i82801aa_lpc_device::gpi_rout_r()
{
	return gpi_rout;
}

void i82801aa_lpc_device::gpi_rout_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&gpi_rout);
	logerror("%s: gpi_rout = %08x\n", tag(), gpi_rout);
}

uint8_t i82801aa_lpc_device::mon_fwd_en_r()
{
	return mon_fwd_en;
}

void i82801aa_lpc_device::mon_fwd_en_w(uint8_t data)
{
	mon_fwd_en = data;
	logerror("%s: mon_fwd_en = %02x\n", tag(), mon_fwd_en);
}

uint16_t i82801aa_lpc_device::mon_trp_rng_r(offs_t offset)
{
	return mon_trp_rng[offset];
}

void i82801aa_lpc_device::mon_trp_rng_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&mon_trp_rng[offset]);
	logerror("%s: mon_trp_rng[%d] = %04x\n", tag(), 4+offset, mon_trp_rng[offset]);
}

uint16_t i82801aa_lpc_device::mon_trp_msk_r()
{
	return mon_trp_msk;
}

void i82801aa_lpc_device::mon_trp_msk_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&mon_trp_msk);
	logerror("%s: mon_trp_msk = %04x\n", tag(), mon_trp_msk);
}

uint32_t i82801aa_lpc_device::gen_cntl_r()
{
	return gen_cntl;
}

void i82801aa_lpc_device::gen_cntl_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&gen_cntl);
	logerror("%s: gen_cntl = %08x\n", tag(), gen_cntl);
}

uint8_t i82801aa_lpc_device::gen_sta_r()
{
	return gen_sta;
}

void i82801aa_lpc_device::gen_sta_w(uint8_t data)
{
	gen_sta = data;
	logerror("%s: gen_sta = %02x\n", tag(), gen_sta);
}

uint8_t i82801aa_lpc_device::back_cntl_r()
{
	return back_cntl;
}

void i82801aa_lpc_device::back_cntl_w(uint8_t data)
{
	back_cntl = data;
	logerror("%s: back_cntl = %02x\n", tag(), back_cntl);
	remap_cb();
}

uint8_t i82801aa_lpc_device::rtc_conf_r()
{
	return rtc_conf;
}

void i82801aa_lpc_device::rtc_conf_w(uint8_t data)
{
	rtc_conf = data;
	logerror("%s: rtc_conf = %02x\n", tag(), rtc_conf);
	remap_cb();
}

uint8_t i82801aa_lpc_device::lpc_if_com_range_r()
{
	return lpc_if_com_range;
}

void i82801aa_lpc_device::lpc_if_com_range_w(uint8_t data)
{
	lpc_if_com_range = data;
	logerror("%s: lpc_if_com_range = %02x\n", tag(), lpc_if_com_range);
	remap_cb();
}

uint8_t i82801aa_lpc_device::lpc_if_fdd_lpt_range_r()
{
	return lpc_if_fdd_lpt_range;
}

void i82801aa_lpc_device::lpc_if_fdd_lpt_range_w(offs_t offset, uint8_t data, uint8_t mem_mask)
{
	COMBINE_DATA(&lpc_if_fdd_lpt_range);
	logerror("%s: lpc_if_fdd_lpt_range  = %02x\n", tag(), lpc_if_fdd_lpt_range);
	remap_cb();
}

uint8_t i82801aa_lpc_device::lpc_if_sound_range_r()
{
	return lpc_if_sound_range;
}

void i82801aa_lpc_device::lpc_if_sound_range_w(offs_t offset, uint8_t data, uint8_t mem_mask)
{
	COMBINE_DATA(&lpc_if_sound_range);
	logerror("%s: lpc_if_sound_range  = %02x\n", tag(), lpc_if_sound_range);
	remap_cb();
}

uint8_t i82801aa_lpc_device::fwh_dec_en1_r()
{
	return fwh_dec_en1;
}

void i82801aa_lpc_device::fwh_dec_en1_w(uint8_t data)
{
	fwh_dec_en1 = data | 0x80;
	logerror("%s: fwh_dec_en1  = %02x\n", tag(), fwh_dec_en1);
	remap_cb();
}

uint16_t i82801aa_lpc_device::gen1_dec_r()
{
	return gen1_dec;
}

void i82801aa_lpc_device::gen1_dec_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&gen1_dec);
	logerror("%s: gen1_dec = %04x\n", tag(), gen1_dec);
	remap_cb();
}

uint16_t i82801aa_lpc_device::lpc_en_r()
{
	return lpc_en;
}

void i82801aa_lpc_device::lpc_en_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&lpc_en);
	logerror("%s: lpc_en = %04x\n", tag(), lpc_en);
	remap_cb();
}

uint32_t i82801aa_lpc_device::fwh_sel1_r()
{
	return fwh_sel1;
}

void i82801aa_lpc_device::fwh_sel1_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&fwh_sel1);
	logerror("%s: fwh_sel1 = %08x\n", tag(), fwh_sel1);
	remap_cb();
}

uint16_t i82801aa_lpc_device::gen2_dec_r()
{
	return gen2_dec;
}

void i82801aa_lpc_device::gen2_dec_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&gen2_dec);
	logerror("%s: gen2_dec = %04x\n", tag(), gen2_dec);
	remap_cb();
}

uint16_t i82801aa_lpc_device::fwh_sel2_r()
{
	return fwh_sel2;
}

void i82801aa_lpc_device::fwh_sel2_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&fwh_sel2);
	logerror("%s: fwh_sel2 = %04x\n", tag(), fwh_sel2);
	remap_cb();
}

uint8_t i82801aa_lpc_device::fwh_dec_en2_r()
{
	return fwh_dec_en2;
}

void i82801aa_lpc_device::fwh_dec_en2_w(uint8_t data)
{
	fwh_dec_en2 = data;
	logerror("%s: fwh_dec_en2  = %02x\n", tag(), fwh_dec_en2);
	remap_cb();
}

uint16_t i82801aa_lpc_device::func_dis_r()
{
	return func_dis;
}

void i82801aa_lpc_device::func_dis_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&func_dis);
	logerror("%s: func_dis = %04x\n", tag(), func_dis);
}

uint32_t i82801aa_lpc_device::etr1_r()
{
	return etr1;
}

void i82801aa_lpc_device::etr1_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	COMBINE_DATA(&etr1);
	logerror("%s: etr1 = %08x\n", tag(), etr1);
}

uint32_t i82801aa_lpc_device::mfid_r()
{
	return 0xf66;
}

uint32_t i82801aa_lpc_device::unk_fc_r()
{
	logerror("%s: read undocumented config reg fc\n", tag());
	return 0;
}

void i82801aa_lpc_device::unk_fc_w(uint32_t data)
{
	logerror("%s: write undocumented config reg fc (%08x)\n", tag(), data);
}



uint8_t i82801aa_lpc_device::siu_config_port_r()
{
	return siu_config_port;
}

void i82801aa_lpc_device::siu_config_port_w(uint8_t data)
{
	siu_config_port = data;
	switch(siu_config_state) {
	case 0:
		siu_config_state = data == 0x80 ? 1 : 0;
		break;
	case 1:
		siu_config_state = data == 0x86 ? 2 : data == 0x80 ? 1 : 0;
		if(siu_config_state == 2)
			logerror("%s: siu configuration active\n", tag());
		break;
	case 2:
		siu_config_state = data == 0x68 ? 3 : 2;
		break;
	case 3:
		siu_config_state = data == 0x08 ? 0 : data == 0x68 ? 3 : 2;
		if(!siu_config_state)
			logerror("%s: siu configuration disabled\n", tag());
		break;
	}
}

uint8_t i82801aa_lpc_device::siu_data_port_r()
{
	logerror("%s: siu config read port %02x\n", tag(), siu_config_port);
	return 0xff;
}

void i82801aa_lpc_device::siu_data_port_w(uint8_t data)
{
	if(siu_config_state < 2) {
		logerror("%s: siu config write port with config disabled (port=%02x, data=%02x)\n", tag(), siu_config_port, data);
		return;
	}
	logerror("%s: siu config write port %02x, %02x\n", tag(), siu_config_port, data);
}

uint8_t i82801aa_lpc_device::nmi_sc_r()
{
	nmi_sc ^= 0x10;
	return nmi_sc;
}

void i82801aa_lpc_device::nmi_sc_w(uint8_t data)
{
	nmi_sc = data;
	logerror("%s: nmi_sc = %02x\n", tag(), nmi_sc);
}


void i82801aa_lpc_device::nop_w(uint8_t data)
{
}

void i82801aa_lpc_device::map_bios(address_space *memory_space, uint32_t start, uint32_t end, int idsel)
{
	// Ignore idsel, a16 inversion for now
	uint32_t mask = m_region->bytes() - 1;
	memory_space->install_rom(start, end, m_region->base() + (start & mask));
}

void i82801aa_lpc_device::map_extra(uint64_t memory_window_start, uint64_t memory_window_end, uint64_t memory_offset, address_space *memory_space,
									uint64_t io_window_start, uint64_t io_window_end, uint64_t io_offset, address_space *io_space)
{
	if(fwh_dec_en1 & 0x80) {
		map_bios(memory_space, 0xfff80000, 0xffffffff, 7);
		map_bios(memory_space, 0xffb80000, 0xffbfffff, 7);
		map_bios(memory_space, 0x000e0000, 0x000fffff, 7);
	}
	if(fwh_dec_en1 & 0x40) {
		map_bios(memory_space, 0xfff00000, 0xfff7ffff, 6);
		map_bios(memory_space, 0xffb00000, 0xffb7ffff, 6);
	}
	if(fwh_dec_en1 & 0x20) {
		map_bios(memory_space, 0xffe80000, 0xffefffff, 5);
		map_bios(memory_space, 0xffa80000, 0xffafffff, 5);
	}
	if(fwh_dec_en1 & 0x10) {
		map_bios(memory_space, 0xffe00000, 0xffe7ffff, 4);
		map_bios(memory_space, 0xffa00000, 0xffa7ffff, 4);
	}
	if(fwh_dec_en1 & 0x08) {
		map_bios(memory_space, 0xffd80000, 0xffdfffff, 3);
		map_bios(memory_space, 0xff980000, 0xff9fffff, 3);
	}
	if(fwh_dec_en1 & 0x04) {
		map_bios(memory_space, 0xffd00000, 0xffd7ffff, 2);
		map_bios(memory_space, 0xff900000, 0xff97ffff, 2);
	}
	if(fwh_dec_en1 & 0x02) {
		map_bios(memory_space, 0xffc80000, 0xffcfffff, 1);
		map_bios(memory_space, 0xff880000, 0xff8fffff, 1);
	}
	if(fwh_dec_en1 & 0x01) {
		map_bios(memory_space, 0xffc00000, 0xffc7ffff, 0);
		map_bios(memory_space, 0xff800000, 0xff87ffff, 0);
	}

	io_space->install_device(0, 0xffff, *this, &i82801aa_lpc_device::internal_io_map);

	if(acpi_cntl & 0x10)
		acpi->map_device(memory_window_start, memory_window_end, 0, memory_space, io_window_start, io_window_end, pmbase, io_space);
	if(gpio_cntl & 0x10)
		logerror("%s: Warning: gpio range enabled at %04x-%04x\n", tag(), gpio_base, gpio_base+63);

	uint32_t hpet = 0xfed00000 + ((gen_cntl & 0x00018000) >> 3);
	logerror("%s: Warning: hpet at %08x-%08x\n", tag(), hpet, hpet+0x3ff);

	if(lpc_en & 0x1000)
		logerror("%s: Warning: superio at 2e-2f\n", tag());
	if(lpc_en & 0x0800)
		logerror("%s: Warning: mcu at 62/66\n", tag());
	if(lpc_en & 0x0400)
		logerror("%s: Warning: mcu at 60/64\n", tag());
	if(lpc_en & 0x0200)
		logerror("%s: Warning: gameport at 208-20f\n", tag());
	if(lpc_en & 0x0100)
		logerror("%s: Warning: gameport at 200-207\n", tag());

	if(lpc_en & 0x0008) {
		uint16_t fdc = lpc_if_fdd_lpt_range & 0x10 ? 0x370 : 0x3f0;
		logerror("%s: Warning: floppy at %04x-%04x\n", tag(), fdc, fdc+7);
	}

	if(lpc_en & 0x0004) {
		static const uint16_t lpt_pos[4] = { 0x378, 0x278, 0x3bc, 0x000 };
		uint16_t lpt = lpt_pos[lpc_if_fdd_lpt_range & 3];
		if(lpt)
			logerror("%s: Warning: lpt at %04x-%04x %04x-%04x\n", tag(), lpt, lpt+7, lpt+0x400, lpt+0x407);
	}

	static const uint16_t com_pos[8] = { 0x3f8, 0x2f8, 0x220, 0x228, 0x238, 0x2e8, 0x338, 0x3e8 };

	if(lpc_en & 0x0002) {
		uint16_t comb = com_pos[(lpc_if_com_range >> 4) & 7];
		logerror("%s: Warning: comb at %04x-%04x\n", tag(), comb, comb+7);
	}

	if(lpc_en & 0x0001) {
		uint16_t coma = com_pos[lpc_if_com_range & 7];
		logerror("%s: Warning: coma at %04x-%04x\n", tag(), coma, coma+7);
	}

	rtc->map_device(memory_window_start, memory_window_end, 0, memory_space, io_window_start, io_window_end, 0, io_space);
	if(rtc_conf & 4)
		rtc->map_extdevice(memory_window_start, memory_window_end, 0, memory_space, io_window_start, io_window_end, 0, io_space);
	pit->map_device(memory_window_start, memory_window_end, 0, memory_space, io_window_start, io_window_end, 0, io_space);
}

void i82801aa_ide_device::config_map(address_map &map)
{
	pci_device::config_map(map);
	map(0x06, 0x07).rw(FUNC(i82801aa_ide_device::status_r), FUNC(i82801aa_ide_device::status_w));
	map(0x0d, 0x0d).rw(FUNC(i82801aa_ide_device::latency_timer_r), FUNC(i82801aa_ide_device::latency_timer_w));
	map(0x10, 0x1f).noprw();
	map(0x20, 0x23).rw(FUNC(i82801aa_ide_device::bmiba_r), FUNC(i82801aa_ide_device::bmiba_w));
	map(0x24, 0x3b).noprw();
	map(0x40, 0x41).rw(FUNC(i82801aa_ide_device::idetim_primary_r), FUNC(i82801aa_ide_device::idetim_primary_w));
	map(0x42, 0x43).rw(FUNC(i82801aa_ide_device::idetim_secondary_r), FUNC(i82801aa_ide_device::idetim_secondary_w));
	map(0x44, 0x44).rw(FUNC(i82801aa_ide_device::sidetim_r), FUNC(i82801aa_ide_device::sidetim_w));
}

void i82801aa_ide_device::internal_io_map(address_map &map)
{
	map(0x0170, 0x0177).rw(FUNC(i82801aa_ide_device::ide2_read32_cs0_r), FUNC(i82801aa_ide_device::ide2_write32_cs0_w));
	map(0x01f0, 0x01f7).rw(FUNC(i82801aa_ide_device::ide1_read32_cs0_r), FUNC(i82801aa_ide_device::ide1_write32_cs0_w));
	map(0x0376, 0x0376).rw(FUNC(i82801aa_ide_device::ide2_read_cs1_r), FUNC(i82801aa_ide_device::ide2_write_cs1_w));
	map(0x03f6, 0x03f6).rw(FUNC(i82801aa_ide_device::ide1_read_cs1_r), FUNC(i82801aa_ide_device::ide1_write_cs1_w));
}

void i82801aa_ide_device::device_add_mconfig(machine_config &config)
{
	BUS_MASTER_IDE_CONTROLLER(config, m_ide1).options(ata_devices, "hdd", nullptr, false);
	m_ide1->irq_handler().set(FUNC(i82801aa_ide_device::primary_int));

	BUS_MASTER_IDE_CONTROLLER(config, m_ide2).options(ata_devices, "cdrom", nullptr, false);
	m_ide2->irq_handler().set(FUNC(i82801aa_ide_device::secondary_int));
}

void i82801aa_ide_device::device_config_complete()
{
	auto ide1 = m_ide1.finder_target();
	auto ide2 = m_ide2.finder_target();
	ide1.first.subdevice<bus_master_ide_controller_device>(ide1.second)->set_bus_master_space(m_maincpu, AS_PROGRAM);
	ide2.first.subdevice<bus_master_ide_controller_device>(ide2.second)->set_bus_master_space(m_maincpu, AS_PROGRAM);

	pci_device::device_config_complete();
}

i82801aa_ide_device::i82801aa_ide_device(const machine_config &mconfig, device_type type, const char *tag, device_t *owner, uint32_t clock)
	: pci_device(mconfig, type, tag, owner, clock)
	, latency_timer(0)
	, bmiba(1)
	, idetim_primary(0)
	, idetim_secondary(0)
	, sidetim(0)
	, m_irq_pri_callback(*this)
	, m_irq_sec_callback(*this)
	, m_maincpu(*this, finder_base::DUMMY_TAG)
	, m_ide1(*this, "ide1")
	, m_ide2(*this, "ide2")
{
}

i82801aa_ide_device::i82801aa_ide_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: i82801aa_ide_device(mconfig, I82801AA_IDE, tag, owner, clock)
{
	set_ids(0x808625a2, 0x02, 0x010180, 0x00000000);
}

void i82801aa_ide_device::device_start()
{
	pci_device::device_start();
	status = 0x0280;
	command = 0;
}

void i82801aa_ide_device::device_reset()
{
}

void i82801aa_ide_device::reset_all_mappings()
{
}

void i82801aa_ide_device::map_extra(
		uint64_t memory_window_start,
		uint64_t memory_window_end,
		uint64_t memory_offset,
		address_space *memory_space,
		uint64_t io_window_start,
		uint64_t io_window_end,
		uint64_t io_offset,
		address_space *io_space)
{
	io_space->install_device(0, 0x3ff, *this, &i82801aa_ide_device::internal_io_map);
	if (command & 1)
	{
		offs_t m_base = bmiba & 0xfff0;

		io_space->install_readwrite_handler(m_base, m_base + 0x7, read32s_delegate(*m_ide1, FUNC(bus_master_ide_controller_device::bmdma_r)), write32s_delegate(*m_ide1, FUNC(bus_master_ide_controller_device::bmdma_w)), 0xffffffff);
		io_space->install_readwrite_handler(m_base + 0x8, m_base + 0xf, read32s_delegate(*m_ide2, FUNC(bus_master_ide_controller_device::bmdma_r)), write32s_delegate(*m_ide2, FUNC(bus_master_ide_controller_device::bmdma_w)), 0xffffffff);
	}
}

void i82801aa_ide_device::primary_int(int state)
{
	m_irq_pri_callback(state);
}

void i82801aa_ide_device::secondary_int(int state)
{
	m_irq_sec_callback(state);
}

void i82801aa_ide_device::status_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	// bits 11-13 are clear on write
	status = status & ~(data & (0x3800 & mem_mask));
	logerror("status = %04x\n", status);
}

uint8_t i82801aa_ide_device::latency_timer_r()
{
	return latency_timer;
}

void i82801aa_ide_device::latency_timer_w(uint8_t data)
{
	latency_timer = data;
	logerror("latency_timer = %02x\n", latency_timer);
}

uint32_t i82801aa_ide_device::bmiba_r()
{
	return bmiba;
}

void i82801aa_ide_device::bmiba_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	mem_mask &= 0xfff0;
	COMBINE_DATA(&bmiba);
	logerror("bmiba = %04x\n", bmiba);
	if (command & 1)
		remap_cb();
}

uint16_t i82801aa_ide_device::idetim_primary_r()
{
	return idetim_primary;
}

void i82801aa_ide_device::idetim_primary_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&idetim_primary);
	logerror("idetim_primary = %04x\n", idetim_primary);
}

uint16_t i82801aa_ide_device::idetim_secondary_r()
{
	return idetim_secondary;
}

void i82801aa_ide_device::idetim_secondary_w(offs_t offset, uint16_t data, uint16_t mem_mask)
{
	COMBINE_DATA(&idetim_secondary);
	logerror("idetim_secondary = %04x\n", idetim_secondary);
}

uint8_t i82801aa_ide_device::sidetim_r()
{
	return sidetim;
}

void i82801aa_ide_device::sidetim_w(uint8_t data)
{
	sidetim = data;
	logerror("sidetim = %02x\n", sidetim);
}

uint32_t i82801aa_ide_device::ide1_read32_cs0_r(offs_t offset, uint32_t mem_mask)
{
	if (!(command & 1))
		return 0xffffffff;
	return m_ide1->read_cs0(offset, mem_mask);
}

void i82801aa_ide_device::ide1_write32_cs0_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	if (!(command & 1))
		return;
	m_ide1->write_cs0(offset, data, mem_mask);
}

uint32_t i82801aa_ide_device::ide2_read32_cs0_r(offs_t offset, uint32_t mem_mask)
{
	if (!(command & 1))
		return 0xffffffff;
	return m_ide2->read_cs0(offset, mem_mask);
}

void i82801aa_ide_device::ide2_write32_cs0_w(offs_t offset, uint32_t data, uint32_t mem_mask)
{
	if (!(command & 1))
		return;
	m_ide2->write_cs0(offset, data, mem_mask);
}

uint8_t i82801aa_ide_device::ide1_read_cs1_r()
{
	if (!(command & 1))
		return 0xff;
	return m_ide1->read_cs1(1, 0xff0000) >> 16;
}

void i82801aa_ide_device::ide1_write_cs1_w(uint8_t data)
{
	if (!(command & 1))
		return;
	m_ide1->write_cs1(1, data << 16, 0xff0000);
}

uint8_t i82801aa_ide_device::ide2_read_cs1_r()
{
	if (!(command & 1))
		return 0xff;
	return m_ide2->read_cs1(1, 0xff0000) >> 16;
}

void i82801aa_ide_device::ide2_write_cs1_w(uint8_t data)
{
	if (!(command & 1))
		return;
	m_ide2->write_cs1(1, data << 16, 0xff0000);
}