// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    Commodore 2031 Single Disk Drive emulation

**********************************************************************/

#include "emu.h"
#include "c2031.h"



//**************************************************************************
//  MACROS / CONSTANTS
//**************************************************************************

#define M6502_TAG       "ucd5"
#define M6522_0_TAG     "uab1"
#define M6522_1_TAG     "ucd4"
#define C64H156_TAG     "64h156"


enum
{
	LED_POWER = 0,
	LED_ACT
};



//**************************************************************************
//  DEVICE DEFINITIONS
//**************************************************************************

DEFINE_DEVICE_TYPE(C2031, c2031_device, "c2031", "Commodore 2031")


//-------------------------------------------------
//  ROM( c2031 )
//-------------------------------------------------

ROM_START( c2031 )
	ROM_REGION( 0x4000, M6502_TAG, 0 )
	ROM_LOAD( "901484-03.u5f", 0x0000, 0x2000, CRC(ee4b893b) SHA1(54d608f7f07860f24186749f21c96724dd48bc50) )
	ROM_LOAD( "901484-05.u5h", 0x2000, 0x2000, CRC(6a629054) SHA1(ec6b75ecfdd4744e5d57979ef6af990444c11ae1) )
ROM_END


//-------------------------------------------------
//  rom_region - device-specific ROM region
//-------------------------------------------------

const tiny_rom_entry *c2031_device::device_rom_region() const
{
	return ROM_NAME( c2031 );
}


//-------------------------------------------------
//  ADDRESS_MAP( c2031_mem )
//-------------------------------------------------

void c2031_device::c2031_mem(address_map &map)
{
	map(0x0000, 0x07ff).mirror(0x6000).ram();
	map(0x1800, 0x180f).mirror(0x63f0).m(M6522_0_TAG, FUNC(via6522_device::map));
	map(0x1c00, 0x1c0f).mirror(0x63f0).m(M6522_1_TAG, FUNC(via6522_device::map));
	map(0x8000, 0xbfff).mirror(0x4000).rom().region(M6502_TAG, 0);
}


void c2031_device::via0_irq_w(int state)
{
	m_via0_irq = state;

	m_maincpu->set_input_line(INPUT_LINE_IRQ0, (m_via0_irq || m_via1_irq) ? ASSERT_LINE : CLEAR_LINE);
}

uint8_t c2031_device::via0_pa_r()
{
	/*

	    bit     description

	    PA0     DI0
	    PA1     DI1
	    PA2     DI2
	    PA3     DI3
	    PA4     DI4
	    PA5     DI5
	    PA6     DI6
	    PA7     DI7

	*/

	return m_bus->dio_r();
}

void c2031_device::via0_pa_w(uint8_t data)
{
	/*

	    bit     description

	    PA0     DI0
	    PA1     DI1
	    PA2     DI2
	    PA3     DI3
	    PA4     DI4
	    PA5     DI5
	    PA6     DI6
	    PA7     DI7

	*/

	m_bus->dio_w(this, data);
}

uint8_t c2031_device::via0_pb_r()
{
	/*

	    bit     description

	    PB0     ATNA
	    PB1     NRFD
	    PB2     NDAC
	    PB3     EOI
	    PB4     T/_R
	    PB5     HD SEL
	    PB6     DAV
	    PB7     _ATN

	*/

	uint8_t data = 0;

	// not ready for data
	data |= m_bus->nrfd_r() << 1;

	// not data accepted
	data |= m_bus->ndac_r() << 2;

	// end or identify
	data |= m_bus->eoi_r() << 3;

	// data valid
	data |= m_bus->dav_r() << 6;

	// attention
	data |= !m_bus->atn_r() << 7;

	return data;
}

void c2031_device::via0_pb_w(uint8_t data)
{
	/*

	    bit     description

	    PB0     ATNA
	    PB1     NRFD
	    PB2     NDAC
	    PB3     EOI
	    PB4     T/_R
	    PB5     HD SEL
	    PB6     DAV
	    PB7     _ATN

	*/

	int atna = BIT(data, 0);
	int nrfd = BIT(data, 1);
	int ndac = BIT(data, 2);

	// not ready for data
	m_nrfd_out = nrfd;

	// not data accepted
	m_ndac_out = ndac;

	// end or identify
	m_bus->eoi_w(this, BIT(data, 3));

	// data valid
	m_bus->dav_w(this, BIT(data, 6));

	// attention acknowledge
	m_atna = atna;

	if ((!m_bus->atn_r()) ^ atna)
	{
		nrfd = ndac = 0;
	}

	m_bus->nrfd_w(this, nrfd);
	m_bus->ndac_w(this, ndac);

	m_via0->write_ca2(get_device_number());
}


void c2031_device::via1_irq_w(int state)
{
	m_via1_irq = state;

	m_maincpu->set_input_line(INPUT_LINE_IRQ0, (m_via0_irq || m_via1_irq) ? ASSERT_LINE : CLEAR_LINE);
}

uint8_t c2031_device::via1_pb_r()
{
	/*

	    bit     signal      description

	    PB0
	    PB1
	    PB2
	    PB3
	    PB4     WPS         write protect sense
	    PB5
	    PB6
	    PB7     SYNC        SYNC detect line

	*/

	uint8_t data = 0;

	// write protect sense
	data |= !m_floppy->wpt_r() << 4;

	// SYNC detect line
	data |= m_ga->sync_r() << 7;

	return data;
}

void c2031_device::via1_pb_w(uint8_t data)
{
	/*

	    bit     signal      description

	    PB0     STP0        stepping motor bit 0
	    PB1     STP1        stepping motor bit 1
	    PB2     MTR         motor ON/OFF
	    PB3     ACT         drive 0 LED
	    PB4
	    PB5     DS0         density select 0
	    PB6     DS1         density select 1
	    PB7     SYNC        SYNC detect line

	*/

	// spindle motor
	m_ga->mtr_w(BIT(data, 2));

	// stepper motor
	m_ga->stp_w(data & 0x03);

	// activity LED
	m_leds[LED_ACT] = BIT(data, 3);

	// density select
	m_ga->ds_w((data >> 5) & 0x03);
}


//-------------------------------------------------
//  C64H156_INTERFACE( ga_intf )
//-------------------------------------------------

void c2031_device::byte_w(int state)
{
	m_maincpu->set_input_line(M6502_SET_OVERFLOW, state);

	m_via1->write_ca1(state);
}


//-------------------------------------------------
//  FLOPPY_FORMATS( floppy_formats )
//-------------------------------------------------

void c2031_device::floppy_formats(format_registration &fr)
{
	fr.add(FLOPPY_D64_FORMAT);
	fr.add(FLOPPY_G64_FORMAT);
}


//-------------------------------------------------
//  device_add_mconfig - add device configuration
//-------------------------------------------------

void c2031_device::device_add_mconfig(machine_config &config)
{
	M6502(config, m_maincpu, XTAL(16'000'000)/16);
	m_maincpu->set_addrmap(AS_PROGRAM, &c2031_device::c2031_mem);

	MOS6522(config, m_via0, XTAL(16'000'000)/16);
	m_via0->readpa_handler().set(FUNC(c2031_device::via0_pa_r));
	m_via0->readpb_handler().set(FUNC(c2031_device::via0_pb_r));
	m_via0->writepa_handler().set(FUNC(c2031_device::via0_pa_w));
	m_via0->writepb_handler().set(FUNC(c2031_device::via0_pb_w));
	m_via0->irq_handler().set(FUNC(c2031_device::via0_irq_w));

	MOS6522(config, m_via1, XTAL(16'000'000)/16);
	m_via1->readpa_handler().set(C64H156_TAG, FUNC(c64h156_device::yb_r));
	m_via1->readpb_handler().set(FUNC(c2031_device::via1_pb_r));
	m_via1->writepa_handler().set(C64H156_TAG, FUNC(c64h156_device::yb_w));
	m_via1->writepb_handler().set(FUNC(c2031_device::via1_pb_w));
	m_via1->ca2_handler().set(C64H156_TAG, FUNC(c64h156_device::soe_w));
	m_via1->cb2_handler().set(C64H156_TAG, FUNC(c64h156_device::oe_w));
	m_via1->irq_handler().set(FUNC(c2031_device::via1_irq_w));

	C64H156(config, m_ga, XTAL(16'000'000));
	m_ga->byte_callback().set(FUNC(c2031_device::byte_w));

	floppy_connector &connector(FLOPPY_CONNECTOR(config, C64H156_TAG":0", 0));
	connector.option_add("525ssqd", FLOPPY_525_SSQD);
	connector.set_default_option("525ssqd");
	connector.set_fixed(true);
	connector.set_formats(c2031_device::floppy_formats);
}


//-------------------------------------------------
//  INPUT_PORTS( c2031 )
//-------------------------------------------------

static INPUT_PORTS_START( c2031 )
	PORT_START("ADDRESS")
	PORT_DIPNAME( 0x03, 0x00, "Device Address" )
	PORT_DIPSETTING(    0x00, "8" )
	PORT_DIPSETTING(    0x01, "9" )
	PORT_DIPSETTING(    0x02, "10" )
	PORT_DIPSETTING(    0x03, "11" )
INPUT_PORTS_END


//-------------------------------------------------
//  input_ports - device-specific input ports
//-------------------------------------------------

ioport_constructor c2031_device::device_input_ports() const
{
	return INPUT_PORTS_NAME( c2031 );
}



//**************************************************************************
//  INLINE HELPERS
//**************************************************************************

//-------------------------------------------------
//  get_device_number -
//-------------------------------------------------

inline int c2031_device::get_device_number()
{
	int state = 1;

	switch ((m_slot->get_address() - 8) & 0x03)
	{
	case 0: state = (m_atna && m_nrfd_out); break;
	case 1: state = m_nrfd_out;             break;
	case 2: state = m_atna;                 break;
	case 3: state = 1;                      break;
	}

	return state;
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  c2031_device - constructor
//-------------------------------------------------

c2031_device::c2031_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, C2031, tag, owner, clock)
	, device_ieee488_interface(mconfig, *this)
	, m_maincpu(*this, M6502_TAG)
	, m_via0(*this, M6522_0_TAG)
	, m_via1(*this, M6522_1_TAG)
	, m_ga(*this, C64H156_TAG)
	, m_floppy(*this, C64H156_TAG":0:525ssqd")
	, m_address(*this, "ADDRESS")
	, m_leds(*this, "led%u", 0U)
	, m_nrfd_out(1)
	, m_ndac_out(1)
	, m_atna(1)
	, m_ifc(0)
	, m_via0_irq(0)
	, m_via1_irq(0)
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void c2031_device::device_start()
{
	m_leds.resolve();
	// install image callbacks
	m_ga->set_floppy(m_floppy);

	// register for state saving
	save_item(NAME(m_nrfd_out));
	save_item(NAME(m_ndac_out));
	save_item(NAME(m_atna));
	save_item(NAME(m_via0_irq));
	save_item(NAME(m_via1_irq));
}


//-------------------------------------------------
//  device_reset - device-specific reset
//-------------------------------------------------

void c2031_device::device_reset()
{
	m_maincpu->reset();

	m_via0->reset();
	m_via1->reset();
}


//-------------------------------------------------
//  ieee488_atn_w -
//-------------------------------------------------

void c2031_device::ieee488_atn(int state)
{
	int nrfd = m_nrfd_out;
	int ndac = m_ndac_out;

	m_via0->write_ca1(!state);

	if ((!state) ^ m_atna)
	{
		nrfd = ndac = 0;
	}

	m_bus->nrfd_w(this, nrfd);
	m_bus->ndac_w(this, ndac);
}


//-------------------------------------------------
//  ieee488_ifc_w -
//-------------------------------------------------

void c2031_device::ieee488_ifc(int state)
{
	if (!m_ifc && state)
	{
		device_reset();
	}

	m_ifc = state;
}
