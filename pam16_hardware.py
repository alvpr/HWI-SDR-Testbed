#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: pam16_hardware
# GNU Radio version: 3.9.0.0

from distutils.version import StrictVersion

if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print("Warning: failed to XInitThreads()")

from PyQt5 import Qt
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import analog
from gnuradio import blocks
import numpy
from gnuradio import digital
from gnuradio import filter
from gnuradio import gr
from gnuradio.fft import window
import sys
import signal
from argparse import ArgumentParser
from gnuradio.eng_arg import eng_float, intx
from gnuradio import eng_notation
from gnuradio import uhd
import time
from gnuradio.filter import pfb
from gnuradio.qtgui import Range, RangeWidget
from PyQt5 import QtCore
import demonstrator
import numpy as np



from gnuradio import qtgui

class pam16_hardware(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "pam16_hardware", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("pam16_hardware")
        qtgui.util.check_set_qss()
        try:
            self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
        except:
            pass
        self.top_scroll_layout = Qt.QVBoxLayout()
        self.setLayout(self.top_scroll_layout)
        self.top_scroll = Qt.QScrollArea()
        self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
        self.top_scroll_layout.addWidget(self.top_scroll)
        self.top_scroll.setWidgetResizable(True)
        self.top_widget = Qt.QWidget()
        self.top_scroll.setWidget(self.top_widget)
        self.top_layout = Qt.QVBoxLayout(self.top_widget)
        self.top_grid_layout = Qt.QGridLayout()
        self.top_layout.addLayout(self.top_grid_layout)

        self.settings = Qt.QSettings("GNU Radio", "pam16_hardware")

        try:
            if StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
                self.restoreGeometry(self.settings.value("geometry").toByteArray())
            else:
                self.restoreGeometry(self.settings.value("geometry"))
        except:
            pass

        ##################################################
        # Variables
        ##################################################
        self.const_base = const_base = digital.constellation_calcdist([-15,1,3,5,7,9,11,13,15,-1,-3,-5,-7,-9,-11,-13], [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
        1, 1, digital.constellation.AMPLITUDE_NORMALIZATION).base()
        self.p = p = const_base.points()
        self.pavg = pavg = np.sum(np.abs(p)**2)/len(p)
        self.snr = snr = 50
        self.pnorm = pnorm = 1
        self.pconst = pconst = p/np.sqrt(pavg)
        self.h2 = h2 = 0.0841 + 0.0364j
        self.h1 = h1 = 0.9159 + 0.0364j
        self.sps = sps = 4
        self.sigma2 = sigma2 = pnorm/(10**(snr/10))
        self.pconst_iq = pconst_iq = h1*pconst + h2*np.conj(pconst)
        self.nfilts = nfilts = 32
        self.excess_bw = excess_bw = 0.35
        self.timing_loop_bw = timing_loop_bw = 6.28/200
        self.sigma = sigma = np.sqrt(sigma2)
        self.samp_rate = samp_rate = 5e6
        self.rrc_taps_tx = rrc_taps_tx = firdes.root_raised_cosine(nfilts, nfilts, 1.0, excess_bw, 11*sps*nfilts)
        self.rrc_taps = rrc_taps = firdes.root_raised_cosine(nfilts, nfilts, 1.0/float(sps), excess_bw, 11*sps*nfilts)
        self.phase_bw = phase_bw = 31e-3/10
        self.pavg_iq = pavg_iq = np.sum(np.abs(pconst_iq)**2)/len(pconst_iq)
        self.mod_avg_iq = mod_avg_iq = np.sum(np.abs(pconst_iq))/len(pconst_iq)
        self.gain_tx = gain_tx = 0
        self.gain_rx = gain_rx = 0
        self.freq = freq = 900e6
        self.d = d = 1/np.sqrt(2)
        self.const_iq = const_iq = digital.constellation_calcdist(pconst_iq, [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
        1, 1, digital.constellation.NO_NORMALIZATION).base()
        self.const = const = digital.constellation_calcdist(pconst, [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
        1, 1, digital.constellation.NO_NORMALIZATION).base()
        self.arity = arity = 4

        ##################################################
        # Blocks
        ##################################################
        self.controls = Qt.QTabWidget()
        self.controls_widget_0 = Qt.QWidget()
        self.controls_layout_0 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.controls_widget_0)
        self.controls_grid_layout_0 = Qt.QGridLayout()
        self.controls_layout_0.addLayout(self.controls_grid_layout_0)
        self.controls.addTab(self.controls_widget_0, 'TX')
        self.controls_widget_1 = Qt.QWidget()
        self.controls_layout_1 = Qt.QBoxLayout(Qt.QBoxLayout.TopToBottom, self.controls_widget_1)
        self.controls_grid_layout_1 = Qt.QGridLayout()
        self.controls_layout_1.addLayout(self.controls_grid_layout_1)
        self.controls.addTab(self.controls_widget_1, 'RX')
        self.top_grid_layout.addWidget(self.controls, 0, 0, 1, 2)
        for r in range(0, 1):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self._timing_loop_bw_range = Range(0.0, 0.1, 0.001, 6.28/200, 200)
        self._timing_loop_bw_win = RangeWidget(self._timing_loop_bw_range, self.set_timing_loop_bw, 'timing_loop_bw', "counter_slider", float, QtCore.Qt.Horizontal)
        self.controls_grid_layout_1.addWidget(self._timing_loop_bw_win, 0, 1, 1, 1)
        for r in range(0, 1):
            self.controls_grid_layout_1.setRowStretch(r, 1)
        for c in range(1, 2):
            self.controls_grid_layout_1.setColumnStretch(c, 1)
        self._phase_bw_range = Range(0.0, 0.1, 0.01, 31e-3/10, 200)
        self._phase_bw_win = RangeWidget(self._phase_bw_range, self.set_phase_bw, 'Phase: Bandwidth', "counter_slider", float, QtCore.Qt.Horizontal)
        self.controls_grid_layout_1.addWidget(self._phase_bw_win, 1, 1, 1, 1)
        for r in range(1, 2):
            self.controls_grid_layout_1.setRowStretch(r, 1)
        for c in range(1, 2):
            self.controls_grid_layout_1.setColumnStretch(c, 1)
        self._snr_range = Range(0, 200, 0.5, 50, 200)
        self._snr_win = RangeWidget(self._snr_range, self.set_snr, 'SNR', "counter_slider", float, QtCore.Qt.Horizontal)
        self.controls_grid_layout_0.addWidget(self._snr_win, 2, 1, 1, 1)
        for r in range(2, 3):
            self.controls_grid_layout_0.setRowStretch(r, 1)
        for c in range(1, 2):
            self.controls_grid_layout_0.setColumnStretch(c, 1)
        self.qtgui_sink_x_1_0 = qtgui.sink_c(
            1024, #fftsize
            window.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "Rx_Signal", #name
            True, #plotfreq
            True, #plotwaterfall
            True, #plottime
            True, #plotconst
            None # parent
        )
        self.qtgui_sink_x_1_0.set_update_time(1.0/10)
        self._qtgui_sink_x_1_0_win = sip.wrapinstance(self.qtgui_sink_x_1_0.pyqwidget(), Qt.QWidget)

        self.qtgui_sink_x_1_0.enable_rf_freq(False)

        self.top_grid_layout.addWidget(self._qtgui_sink_x_1_0_win, 1, 1, 1, 1)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_sink_x_1 = qtgui.sink_c(
            1024, #fftsize
            window.WIN_BLACKMAN_hARRIS, #wintype
            0, #fc
            samp_rate, #bw
            "Tx_Signal", #name
            True, #plotfreq
            True, #plotwaterfall
            True, #plottime
            True, #plotconst
            None # parent
        )
        self.qtgui_sink_x_1.set_update_time(1.0/10)
        self._qtgui_sink_x_1_win = sip.wrapinstance(self.qtgui_sink_x_1.pyqwidget(), Qt.QWidget)

        self.qtgui_sink_x_1.enable_rf_freq(False)

        self.top_grid_layout.addWidget(self._qtgui_sink_x_1_win, 1, 0, 1, 1)
        for r in range(1, 2):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_1 = qtgui.const_sink_c(
            1024, #size
            'Tx HWI', #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_1.set_update_time(0.10)
        self.qtgui_const_sink_x_1.set_y_axis(-1.5, 1.5)
        self.qtgui_const_sink_x_1.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_1.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_1.enable_autoscale(False)
        self.qtgui_const_sink_x_1.enable_grid(True)
        self.qtgui_const_sink_x_1.enable_axis_labels(True)


        labels = ["C", '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_1.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_1.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_1.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_1.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_1.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_1.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_1.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_1_win = sip.wrapinstance(self.qtgui_const_sink_x_1.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_1_win, 2, 1, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(1, 2):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.qtgui_const_sink_x_0 = qtgui.const_sink_c(
            256*4, #size
            "Rx", #name
            1, #number of inputs
            None # parent
        )
        self.qtgui_const_sink_x_0.set_update_time(0.10)
        self.qtgui_const_sink_x_0.set_y_axis(-1.5, 1.5)
        self.qtgui_const_sink_x_0.set_x_axis(-2, 2)
        self.qtgui_const_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, qtgui.TRIG_SLOPE_POS, 0.0, 0, "")
        self.qtgui_const_sink_x_0.enable_autoscale(False)
        self.qtgui_const_sink_x_0.enable_grid(True)
        self.qtgui_const_sink_x_0.enable_axis_labels(True)


        labels = ['Con', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "red", "red", "red",
            "red", "red", "red", "red", "red"]
        styles = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        markers = [0, 0, 0, 0, 0,
            0, 0, 0, 0, 0]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_const_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_const_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_const_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_const_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_const_sink_x_0.set_line_style(i, styles[i])
            self.qtgui_const_sink_x_0.set_line_marker(i, markers[i])
            self.qtgui_const_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_const_sink_x_0_win = sip.wrapinstance(self.qtgui_const_sink_x_0.pyqwidget(), Qt.QWidget)
        self.top_grid_layout.addWidget(self._qtgui_const_sink_x_0_win, 2, 0, 1, 1)
        for r in range(2, 3):
            self.top_grid_layout.setRowStretch(r, 1)
        for c in range(0, 1):
            self.top_grid_layout.setColumnStretch(c, 1)
        self.uhd_usrp_source_0_0 = uhd.usrp_source(
            ",".join(("addr0=192.168.1.151", "")),
            uhd.stream_args(
                cpu_format="fc32",
                args='',
                channels=list(range(0,1)),
            ),
        )
        self.uhd_usrp_source_0_0.set_samp_rate(samp_rate)
        # No synchronization enforced.

        self.uhd_usrp_source_0_0.set_center_freq(freq, 0)
        self.uhd_usrp_source_0_0.set_antenna("TX/RX", 0)
        self.uhd_usrp_source_0_0.set_rx_agc(False, 0)
        self.uhd_usrp_source_0_0.set_gain(gain_rx, 0)
        self.uhd_usrp_source_0_0.set_auto_dc_offset(True, 0)
        self.uhd_usrp_source_0_0.set_auto_iq_balance(False, 0)
        self.uhd_usrp_sink_0_0 = uhd.usrp_sink(
            ",".join(("addr0=192.168.1.150", "")),
            uhd.stream_args(
                cpu_format="fc32",
                args='',
                channels=list(range(0,1)),
            ),
            '',
        )
        self.uhd_usrp_sink_0_0.set_samp_rate(samp_rate)
        # No synchronization enforced.

        self.uhd_usrp_sink_0_0.set_center_freq(freq, 0)
        self.uhd_usrp_sink_0_0.set_antenna("TX/RX", 0)
        self.uhd_usrp_sink_0_0.set_gain(gain_tx, 0)
        self.qtgui_number_sink_0 = qtgui.number_sink(
            gr.sizeof_float,
            0,
            qtgui.NUM_GRAPH_HORIZ,
            1,
            None # parent
        )
        self.qtgui_number_sink_0.set_update_time(0.10)
        self.qtgui_number_sink_0.set_title("")

        labels = ['', '', '', '', '',
            '', '', '', '', '']
        units = ['', '', '', '', '',
            '', '', '', '', '']
        colors = [("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"),
            ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black"), ("black", "black")]
        factor = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]

        for i in range(1):
            self.qtgui_number_sink_0.set_min(i, -1)
            self.qtgui_number_sink_0.set_max(i, 1)
            self.qtgui_number_sink_0.set_color(i, colors[i][0], colors[i][1])
            if len(labels[i]) == 0:
                self.qtgui_number_sink_0.set_label(i, "Data {0}".format(i))
            else:
                self.qtgui_number_sink_0.set_label(i, labels[i])
            self.qtgui_number_sink_0.set_unit(i, units[i])
            self.qtgui_number_sink_0.set_factor(i, factor[i])

        self.qtgui_number_sink_0.enable_autoscale(False)
        self._qtgui_number_sink_0_win = sip.wrapinstance(self.qtgui_number_sink_0.pyqwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_number_sink_0_win)
        self.pfb_arb_resampler_xxx_0 = pfb.arb_resampler_ccf(
            sps,
            taps=rrc_taps_tx,
            flt_size=nfilts)
        self.pfb_arb_resampler_xxx_0.declare_sample_delay(0)
        self.digital_symbol_sync_xx_1 = digital.symbol_sync_cc(
            digital.TED_SIGNAL_TIMES_SLOPE_ML,
            sps,
            timing_loop_bw,
            1.0,
            1.0,
            1.5,
            1,
            const.base(),
            digital.IR_PFB_MF,
            nfilts,
            rrc_taps)
        self.digital_diff_encoder_bb_0 = digital.diff_encoder_bb(16)
        self.digital_diff_decoder_bb_0_0_0_0 = digital.diff_decoder_bb(16)
        self.digital_crc32_bb_0 = digital.crc32_bb(False, "packet_len", True)
        self.digital_correlate_access_code_xx_ts_0 = digital.correlate_access_code_bb_ts('11100001010110101110100010010011',
          0, 'payload_len')
        self.digital_constellation_receiver_cb_0 = digital.constellation_receiver_cb(const_iq, phase_bw, -0.5, 0.5)
        self.digital_constellation_decoder_cb_0_0 = digital.constellation_decoder_cb(const_iq)
        self.digital_chunks_to_symbols_xx_0 = digital.chunks_to_symbols_bc(const.points(), 1)
        self.demonstrator_crc32_check_0 = demonstrator.crc32_check(1000, 200, 1)
        self.blocks_vector_source_x_1 = blocks.vector_source_b([225,90,232,147,0,104,0,104], True, 1, [])
        self.blocks_unpack_k_bits_bb_0 = blocks.unpack_k_bits_bb(const.bits_per_symbol())
        self.blocks_tagged_stream_to_pdu_0_0 = blocks.tagged_stream_to_pdu(blocks.byte_t, 'payload_len')
        self.blocks_stream_to_tagged_stream_0 = blocks.stream_to_tagged_stream(gr.sizeof_char, 1, 100, "packet_len")
        self.blocks_stream_mux_0 = blocks.stream_mux(gr.sizeof_char*1, [8,104])
        self.blocks_repack_bits_bb_0_1_0 = blocks.repack_bits_bb(1, 8, 'payload_len', False, gr.GR_MSB_FIRST)
        self.blocks_packed_to_unpacked_xx_0 = blocks.packed_to_unpacked_bb(const.bits_per_symbol(), gr.GR_MSB_FIRST)
        self.blocks_null_sink_0_0_1 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_null_sink_0_0_0 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_null_sink_0_0 = blocks.null_sink(gr.sizeof_float*1)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_char*1)
        self.blocks_multiply_const_vxx_2_1 = blocks.multiply_const_cc(h1)
        self.blocks_multiply_const_vxx_2_0_0 = blocks.multiply_const_cc(h2)
        self.blocks_multiply_const_vxx_2_0 = blocks.multiply_const_cc(h2)
        self.blocks_multiply_const_vxx_2 = blocks.multiply_const_cc(h1)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_cc(0.1)
        self.blocks_moving_average_xx_0 = blocks.moving_average_ff(100000, 0.00001, 4000, 1)
        self.blocks_conjugate_cc_0_0 = blocks.conjugate_cc()
        self.blocks_conjugate_cc_0 = blocks.conjugate_cc()
        self.blocks_complex_to_mag_squared_0 = blocks.complex_to_mag_squared(1)
        self.blocks_add_xx_0_1 = blocks.add_vcc(1)
        self.blocks_add_xx_0_0 = blocks.add_vcc(1)
        self.blocks_add_xx_0 = blocks.add_vcc(1)
        self.analog_random_source_x_0 = blocks.vector_source_b(list(map(int, numpy.random.randint(0, 256, 10000000))), True)
        self.analog_noise_source_x_0 = analog.noise_source_c(analog.GR_GAUSSIAN, sigma*np.sqrt(sps), 0)
        self.analog_agc_xx_0_0 = analog.agc_cc(1e-4, mod_avg_iq, 1.0)
        self.analog_agc_xx_0_0.set_max_gain(65536)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.blocks_tagged_stream_to_pdu_0_0, 'pdus'), (self.demonstrator_crc32_check_0, 'in'))
        self.connect((self.analog_agc_xx_0_0, 0), (self.digital_symbol_sync_xx_1, 0))
        self.connect((self.analog_noise_source_x_0, 0), (self.blocks_add_xx_0_1, 1))
        self.connect((self.analog_random_source_x_0, 0), (self.blocks_stream_to_tagged_stream_0, 0))
        self.connect((self.blocks_add_xx_0, 0), (self.blocks_add_xx_0_1, 0))
        self.connect((self.blocks_add_xx_0_0, 0), (self.qtgui_const_sink_x_1, 0))
        self.connect((self.blocks_add_xx_0_1, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.blocks_add_xx_0_1, 0), (self.qtgui_sink_x_1, 0))
        self.connect((self.blocks_complex_to_mag_squared_0, 0), (self.blocks_moving_average_xx_0, 0))
        self.connect((self.blocks_conjugate_cc_0, 0), (self.blocks_multiply_const_vxx_2_0, 0))
        self.connect((self.blocks_conjugate_cc_0_0, 0), (self.blocks_multiply_const_vxx_2_0_0, 0))
        self.connect((self.blocks_moving_average_xx_0, 0), (self.qtgui_number_sink_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.uhd_usrp_sink_0_0, 0))
        self.connect((self.blocks_multiply_const_vxx_2, 0), (self.blocks_add_xx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_2_0, 0), (self.blocks_add_xx_0, 1))
        self.connect((self.blocks_multiply_const_vxx_2_0_0, 0), (self.blocks_add_xx_0_0, 1))
        self.connect((self.blocks_multiply_const_vxx_2_1, 0), (self.blocks_add_xx_0_0, 0))
        self.connect((self.blocks_packed_to_unpacked_xx_0, 0), (self.digital_diff_encoder_bb_0, 0))
        self.connect((self.blocks_repack_bits_bb_0_1_0, 0), (self.blocks_tagged_stream_to_pdu_0_0, 0))
        self.connect((self.blocks_stream_mux_0, 0), (self.blocks_packed_to_unpacked_xx_0, 0))
        self.connect((self.blocks_stream_to_tagged_stream_0, 0), (self.digital_crc32_bb_0, 0))
        self.connect((self.blocks_unpack_k_bits_bb_0, 0), (self.digital_correlate_access_code_xx_ts_0, 0))
        self.connect((self.blocks_vector_source_x_1, 0), (self.blocks_stream_mux_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_conjugate_cc_0_0, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.blocks_multiply_const_vxx_2_1, 0))
        self.connect((self.digital_chunks_to_symbols_xx_0, 0), (self.pfb_arb_resampler_xxx_0, 0))
        self.connect((self.digital_constellation_decoder_cb_0_0, 0), (self.digital_diff_decoder_bb_0_0_0_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 4), (self.blocks_complex_to_mag_squared_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 1), (self.blocks_null_sink_0_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 2), (self.blocks_null_sink_0_0_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 3), (self.blocks_null_sink_0_0_1, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 4), (self.digital_constellation_decoder_cb_0_0, 0))
        self.connect((self.digital_constellation_receiver_cb_0, 4), (self.qtgui_const_sink_x_0, 0))
        self.connect((self.digital_correlate_access_code_xx_ts_0, 0), (self.blocks_repack_bits_bb_0_1_0, 0))
        self.connect((self.digital_crc32_bb_0, 0), (self.blocks_stream_mux_0, 1))
        self.connect((self.digital_diff_decoder_bb_0_0_0_0, 0), (self.blocks_unpack_k_bits_bb_0, 0))
        self.connect((self.digital_diff_encoder_bb_0, 0), (self.digital_chunks_to_symbols_xx_0, 0))
        self.connect((self.digital_symbol_sync_xx_1, 0), (self.digital_constellation_receiver_cb_0, 0))
        self.connect((self.pfb_arb_resampler_xxx_0, 0), (self.blocks_conjugate_cc_0, 0))
        self.connect((self.pfb_arb_resampler_xxx_0, 0), (self.blocks_multiply_const_vxx_2, 0))
        self.connect((self.uhd_usrp_source_0_0, 0), (self.analog_agc_xx_0_0, 0))
        self.connect((self.uhd_usrp_source_0_0, 0), (self.qtgui_sink_x_1_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "pam16_hardware")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_const_base(self):
        return self.const_base

    def set_const_base(self, const_base):
        self.const_base = const_base

    def get_p(self):
        return self.p

    def set_p(self, p):
        self.p = p
        self.set_pavg(np.sum(np.abs(self.p)**2)/len(self.p))
        self.set_pconst(self.p/np.sqrt(self.pavg))

    def get_pavg(self):
        return self.pavg

    def set_pavg(self, pavg):
        self.pavg = pavg
        self.set_pconst(self.p/np.sqrt(self.pavg))

    def get_snr(self):
        return self.snr

    def set_snr(self, snr):
        self.snr = snr
        self.set_sigma2(self.pnorm/(10**(self.snr/10)))

    def get_pnorm(self):
        return self.pnorm

    def set_pnorm(self, pnorm):
        self.pnorm = pnorm
        self.set_sigma2(self.pnorm/(10**(self.snr/10)))

    def get_pconst(self):
        return self.pconst

    def set_pconst(self, pconst):
        self.pconst = pconst
        self.set_pconst_iq(self.h1*self.pconst + self.h2*np.conj(self.pconst))

    def get_h2(self):
        return self.h2

    def set_h2(self, h2):
        self.h2 = h2
        self.set_pconst_iq(self.h1*self.pconst + self.h2*np.conj(self.pconst))
        self.blocks_multiply_const_vxx_2_0.set_k(self.h2)
        self.blocks_multiply_const_vxx_2_0_0.set_k(self.h2)

    def get_h1(self):
        return self.h1

    def set_h1(self, h1):
        self.h1 = h1
        self.set_pconst_iq(self.h1*self.pconst + self.h2*np.conj(self.pconst))
        self.blocks_multiply_const_vxx_2.set_k(self.h1)
        self.blocks_multiply_const_vxx_2_1.set_k(self.h1)

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))
        self.set_rrc_taps_tx(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0, self.excess_bw, 11*self.sps*self.nfilts))
        self.analog_noise_source_x_0.set_amplitude(self.sigma*np.sqrt(self.sps))
        self.pfb_arb_resampler_xxx_0.set_rate(self.sps)

    def get_sigma2(self):
        return self.sigma2

    def set_sigma2(self, sigma2):
        self.sigma2 = sigma2
        self.set_sigma(np.sqrt(self.sigma2))

    def get_pconst_iq(self):
        return self.pconst_iq

    def set_pconst_iq(self, pconst_iq):
        self.pconst_iq = pconst_iq
        self.set_mod_avg_iq(np.sum(np.abs(self.pconst_iq))/len(self.pconst_iq))
        self.set_pavg_iq(np.sum(np.abs(self.pconst_iq)**2)/len(self.pconst_iq))

    def get_nfilts(self):
        return self.nfilts

    def set_nfilts(self, nfilts):
        self.nfilts = nfilts
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))
        self.set_rrc_taps_tx(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0, self.excess_bw, 11*self.sps*self.nfilts))

    def get_excess_bw(self):
        return self.excess_bw

    def set_excess_bw(self, excess_bw):
        self.excess_bw = excess_bw
        self.set_rrc_taps(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0/float(self.sps), self.excess_bw, 11*self.sps*self.nfilts))
        self.set_rrc_taps_tx(firdes.root_raised_cosine(self.nfilts, self.nfilts, 1.0, self.excess_bw, 11*self.sps*self.nfilts))

    def get_timing_loop_bw(self):
        return self.timing_loop_bw

    def set_timing_loop_bw(self, timing_loop_bw):
        self.timing_loop_bw = timing_loop_bw
        self.digital_symbol_sync_xx_1.set_loop_bandwidth(self.timing_loop_bw)

    def get_sigma(self):
        return self.sigma

    def set_sigma(self, sigma):
        self.sigma = sigma
        self.analog_noise_source_x_0.set_amplitude(self.sigma*np.sqrt(self.sps))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.qtgui_sink_x_1.set_frequency_range(0, self.samp_rate)
        self.qtgui_sink_x_1_0.set_frequency_range(0, self.samp_rate)
        self.uhd_usrp_sink_0_0.set_samp_rate(self.samp_rate)
        self.uhd_usrp_source_0_0.set_samp_rate(self.samp_rate)

    def get_rrc_taps_tx(self):
        return self.rrc_taps_tx

    def set_rrc_taps_tx(self, rrc_taps_tx):
        self.rrc_taps_tx = rrc_taps_tx
        self.pfb_arb_resampler_xxx_0.set_taps(self.rrc_taps_tx)

    def get_rrc_taps(self):
        return self.rrc_taps

    def set_rrc_taps(self, rrc_taps):
        self.rrc_taps = rrc_taps

    def get_phase_bw(self):
        return self.phase_bw

    def set_phase_bw(self, phase_bw):
        self.phase_bw = phase_bw

    def get_pavg_iq(self):
        return self.pavg_iq

    def set_pavg_iq(self, pavg_iq):
        self.pavg_iq = pavg_iq

    def get_mod_avg_iq(self):
        return self.mod_avg_iq

    def set_mod_avg_iq(self, mod_avg_iq):
        self.mod_avg_iq = mod_avg_iq
        self.analog_agc_xx_0_0.set_reference(self.mod_avg_iq)

    def get_gain_tx(self):
        return self.gain_tx

    def set_gain_tx(self, gain_tx):
        self.gain_tx = gain_tx
        self.uhd_usrp_sink_0_0.set_gain(self.gain_tx, 0)

    def get_gain_rx(self):
        return self.gain_rx

    def set_gain_rx(self, gain_rx):
        self.gain_rx = gain_rx
        self.uhd_usrp_source_0_0.set_gain(self.gain_rx, 0)

    def get_freq(self):
        return self.freq

    def set_freq(self, freq):
        self.freq = freq
        self.uhd_usrp_sink_0_0.set_center_freq(self.freq, 0)
        self.uhd_usrp_source_0_0.set_center_freq(self.freq, 0)

    def get_d(self):
        return self.d

    def set_d(self, d):
        self.d = d

    def get_const_iq(self):
        return self.const_iq

    def set_const_iq(self, const_iq):
        self.const_iq = const_iq

    def get_const(self):
        return self.const

    def set_const(self, const):
        self.const = const

    def get_arity(self):
        return self.arity

    def set_arity(self, arity):
        self.arity = arity




def main(top_block_cls=pam16_hardware, options=None):

    if StrictVersion("4.5.0") <= StrictVersion(Qt.qVersion()) < StrictVersion("5.0.0"):
        style = gr.prefs().get_string('qtgui', 'style', 'raster')
        Qt.QApplication.setGraphicsSystem(style)
    qapp = Qt.QApplication(sys.argv)

    tb = top_block_cls()

    tb.start()

    tb.show()

    def sig_handler(sig=None, frame=None):
        tb.stop()
        tb.wait()

        Qt.QApplication.quit()

    signal.signal(signal.SIGINT, sig_handler)
    signal.signal(signal.SIGTERM, sig_handler)

    timer = Qt.QTimer()
    timer.start(500)
    timer.timeout.connect(lambda: None)

    qapp.exec_()

if __name__ == '__main__':
    main()
