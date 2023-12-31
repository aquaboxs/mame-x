// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

  RIOT 6532 emulation

***************************************************************************/

#pragma once

#ifndef __RIOT6532_H__
#define __RIOT6532_H__



/***************************************************************************
    TYPE DEFINITIONS
***************************************************************************/


// ======================> riot6532_device

class riot6532_device :  public device_t
{
public:
	// construction/destruction
	riot6532_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock);

	auto in_pa_callback() { return m_in_pa_cb.bind(); }
	auto out_pa_callback() { return m_out_pa_cb.bind(); }
	auto in_pb_callback() { return m_in_pb_cb.bind(); }
	auto out_pb_callback() { return m_out_pb_cb.bind(); }
	auto irq_callback() { return m_irq_cb.bind(); }

	uint8_t read(offs_t offset);
	void write(offs_t offset, uint8_t data);

	uint8_t reg_r(uint8_t offset, bool debugger_access = false);
	void reg_w(uint8_t offset, uint8_t data);

	void porta_in_set(uint8_t data, uint8_t mask);
	void portb_in_set(uint8_t data, uint8_t mask);

	void pa0_w(int state);
	void pa1_w(int state);
	void pa2_w(int state);
	void pa3_w(int state);
	void pa4_w(int state);
	void pa5_w(int state);
	void pa6_w(int state);
	void pa7_w(int state);
	void pb0_w(int state);
	void pb1_w(int state);
	void pb2_w(int state);
	void pb3_w(int state);
	void pb4_w(int state);
	void pb5_w(int state);
	void pb6_w(int state);
	void pb7_w(int state);

	uint8_t porta_in_get();
	uint8_t portb_in_get();

	uint8_t porta_out_get();
	uint8_t portb_out_get();

protected:
	class riot6532_port
	{
	public:
		uint8_t                   m_in;
		uint8_t                   m_out;
		uint8_t                   m_ddr;
		devcb_read8             *m_in_cb;
		devcb_write8            *m_out_cb;
	};

	// device-level overrides
	virtual void device_start() override;
	virtual void device_reset() override;
	virtual void device_post_load() override { }
	virtual void device_clock_changed() override { }

	TIMER_CALLBACK_MEMBER(timer_end);

private:
	void update_irqstate();
	uint8_t apply_ddr(const riot6532_port *port);
	void update_pa7_state();
	uint8_t get_timer();

	riot6532_port     m_port[2];

	devcb_read8       m_in_pa_cb;
	devcb_write8      m_out_pa_cb;
	devcb_read8       m_in_pb_cb;
	devcb_write8      m_out_pb_cb;
	devcb_write_line  m_irq_cb;

	uint8_t           m_irqstate;
	uint8_t           m_irqenable;
	int               m_irq;

	uint8_t           m_pa7dir;     /* 0x80 = high-to-low, 0x00 = low-to-high */
	uint8_t           m_pa7prev;

	uint8_t           m_timershift;
	uint8_t           m_timerstate;
	emu_timer *       m_timer;
};


// device type definition
DECLARE_DEVICE_TYPE(RIOT6532, riot6532_device)

#endif
