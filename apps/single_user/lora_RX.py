#!/usr/bin/env python3
# -*- coding: utf-8 -*-

#
# SPDX-License-Identifier: GPL-3.0
#
# GNU Radio Python Flow Graph
# Title: Lora Rx
# GNU Radio version: 3.9.4.0

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
from PyQt5.QtCore import QObject, pyqtSlot
from gnuradio import qtgui
from gnuradio.filter import firdes
import sip
from gnuradio import blocks
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
import lora_sdr



from gnuradio import qtgui

class lora_RX(gr.top_block, Qt.QWidget):

    def __init__(self):
        gr.top_block.__init__(self, "Lora Rx", catch_exceptions=True)
        Qt.QWidget.__init__(self)
        self.setWindowTitle("Lora Rx")
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

        self.settings = Qt.QSettings("GNU Radio", "lora_RX")

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
        self.samp_rate = samp_rate = 125000
        self.sf = sf = 7
        self.pay_len = pay_len = 11
        self.impl_head = impl_head = False
        self.has_crc = has_crc = False
        self.cr = cr = 1
        self.center_freq = center_freq = 868e6
        self.bw = bw = samp_rate

        ##################################################
        # Blocks
        ##################################################
        # Create the options list
        self._sf_options = [7, 8, 9, 10, 11, 12]
        # Create the labels list
        self._sf_labels = map(str, self._sf_options)
        # Create the combo box
        self._sf_tool_bar = Qt.QToolBar(self)
        self._sf_tool_bar.addWidget(Qt.QLabel("Spreading Factor" + ": "))
        self._sf_combo_box = Qt.QComboBox()
        self._sf_tool_bar.addWidget(self._sf_combo_box)
        for _label in self._sf_labels: self._sf_combo_box.addItem(_label)
        self._sf_callback = lambda i: Qt.QMetaObject.invokeMethod(self._sf_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._sf_options.index(i)))
        self._sf_callback(self.sf)
        self._sf_combo_box.currentIndexChanged.connect(
            lambda i: self.set_sf(self._sf_options[i]))
        # Create the radio buttons
        self.top_layout.addWidget(self._sf_tool_bar)
        _impl_head_check_box = Qt.QCheckBox("Implicit header")
        self._impl_head_choices = {True: True, False: False}
        self._impl_head_choices_inv = dict((v,k) for k,v in self._impl_head_choices.items())
        self._impl_head_callback = lambda i: Qt.QMetaObject.invokeMethod(_impl_head_check_box, "setChecked", Qt.Q_ARG("bool", self._impl_head_choices_inv[i]))
        self._impl_head_callback(self.impl_head)
        _impl_head_check_box.stateChanged.connect(lambda i: self.set_impl_head(self._impl_head_choices[bool(i)]))
        self.top_layout.addWidget(_impl_head_check_box)
        _has_crc_check_box = Qt.QCheckBox("CRC in header")
        self._has_crc_choices = {True: True, False: False}
        self._has_crc_choices_inv = dict((v,k) for k,v in self._has_crc_choices.items())
        self._has_crc_callback = lambda i: Qt.QMetaObject.invokeMethod(_has_crc_check_box, "setChecked", Qt.Q_ARG("bool", self._has_crc_choices_inv[i]))
        self._has_crc_callback(self.has_crc)
        _has_crc_check_box.stateChanged.connect(lambda i: self.set_has_crc(self._has_crc_choices[bool(i)]))
        self.top_layout.addWidget(_has_crc_check_box)
        # Create the options list
        self._cr_options = [1, 2, 3, 4]
        # Create the labels list
        self._cr_labels = ['1', '2', '3', '4']
        # Create the combo box
        self._cr_tool_bar = Qt.QToolBar(self)
        self._cr_tool_bar.addWidget(Qt.QLabel("Coding Rate" + ": "))
        self._cr_combo_box = Qt.QComboBox()
        self._cr_tool_bar.addWidget(self._cr_combo_box)
        for _label in self._cr_labels: self._cr_combo_box.addItem(_label)
        self._cr_callback = lambda i: Qt.QMetaObject.invokeMethod(self._cr_combo_box, "setCurrentIndex", Qt.Q_ARG("int", self._cr_options.index(i)))
        self._cr_callback(self.cr)
        self._cr_combo_box.currentIndexChanged.connect(
            lambda i: self.set_cr(self._cr_options[i]))
        # Create the radio buttons
        self.top_layout.addWidget(self._cr_tool_bar)
        self.uhd_usrp_source_0 = uhd.usrp_source(
            ",".join(('', '')),
            uhd.stream_args(
                cpu_format="fc32",
                args='',
                channels=list(range(0,1)),
            ),
        )
        self.uhd_usrp_source_0.set_samp_rate(samp_rate)
        # No synchronization enforced.

        self.uhd_usrp_source_0.set_center_freq(center_freq, 0)
        self.uhd_usrp_source_0.set_antenna("TX/RX", 0)
        self.uhd_usrp_source_0.set_normalized_gain(0.5, 0)
        self.qtgui_freq_sink_x_0 = qtgui.freq_sink_c(
            1024, #size
            window.WIN_BLACKMAN_hARRIS, #wintype
            center_freq, #fc
            samp_rate, #bw
            "", #name
            1,
            None # parent
        )
        self.qtgui_freq_sink_x_0.set_update_time(0.10)
        self.qtgui_freq_sink_x_0.set_y_axis(-140, 10)
        self.qtgui_freq_sink_x_0.set_y_label('Relative Gain', 'dB')
        self.qtgui_freq_sink_x_0.set_trigger_mode(qtgui.TRIG_MODE_FREE, 0.0, 0, "")
        self.qtgui_freq_sink_x_0.enable_autoscale(False)
        self.qtgui_freq_sink_x_0.enable_grid(False)
        self.qtgui_freq_sink_x_0.set_fft_average(1.0)
        self.qtgui_freq_sink_x_0.enable_axis_labels(True)
        self.qtgui_freq_sink_x_0.enable_control_panel(False)
        self.qtgui_freq_sink_x_0.set_fft_window_normalized(False)



        labels = ['', '', '', '', '',
            '', '', '', '', '']
        widths = [1, 1, 1, 1, 1,
            1, 1, 1, 1, 1]
        colors = ["blue", "red", "green", "black", "cyan",
            "magenta", "yellow", "dark red", "dark green", "dark blue"]
        alphas = [1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0]

        for i in range(1):
            if len(labels[i]) == 0:
                self.qtgui_freq_sink_x_0.set_line_label(i, "Data {0}".format(i))
            else:
                self.qtgui_freq_sink_x_0.set_line_label(i, labels[i])
            self.qtgui_freq_sink_x_0.set_line_width(i, widths[i])
            self.qtgui_freq_sink_x_0.set_line_color(i, colors[i])
            self.qtgui_freq_sink_x_0.set_line_alpha(i, alphas[i])

        self._qtgui_freq_sink_x_0_win = sip.wrapinstance(self.qtgui_freq_sink_x_0.qwidget(), Qt.QWidget)
        self.top_layout.addWidget(self._qtgui_freq_sink_x_0_win)
        self.lora_sdr_header_decoder_0 = lora_sdr.header_decoder(impl_head, cr, pay_len, has_crc)
        self.lora_sdr_hamming_dec_0 = lora_sdr.hamming_dec()
        self.lora_sdr_gray_enc_0 = lora_sdr.gray_enc()
        self.lora_sdr_frame_sync_0 = lora_sdr.frame_sync(bw, bw, sf, impl_head, [18])
        self.lora_sdr_fft_demod_0 = lora_sdr.fft_demod( sf, impl_head)
        self.lora_sdr_dewhitening_0 = lora_sdr.dewhitening()
        self.lora_sdr_deinterleaver_0 = lora_sdr.deinterleaver(sf)
        self.lora_sdr_crc_verif_0 = lora_sdr.crc_verif()
        self.interp_fir_filter_xxx_0 = filter.interp_fir_filter_ccf(4, (-0.128616616593872,	-0.212206590789194,	-0.180063263231421,	3.89817183251938e-17	,0.300105438719035	,0.636619772367581	,0.900316316157106,	1	,0.900316316157106,	0.636619772367581,	0.300105438719035,	3.89817183251938e-17,	-0.180063263231421,	-0.212206590789194,	-0.128616616593872))
        self.interp_fir_filter_xxx_0.declare_sample_delay(0)
        self.blocks_null_sink_0 = blocks.null_sink(gr.sizeof_char*1)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, '/tmp/test.txt', False)
        self.blocks_file_sink_0.set_unbuffered(False)



        ##################################################
        # Connections
        ##################################################
        self.msg_connect((self.lora_sdr_header_decoder_0, 'frame_info'), (self.lora_sdr_frame_sync_0, 'frame_info'))
        self.connect((self.interp_fir_filter_xxx_0, 0), (self.lora_sdr_frame_sync_0, 0))
        self.connect((self.lora_sdr_crc_verif_0, 0), (self.blocks_file_sink_0, 0))
        self.connect((self.lora_sdr_crc_verif_0, 0), (self.blocks_null_sink_0, 0))
        self.connect((self.lora_sdr_deinterleaver_0, 0), (self.lora_sdr_hamming_dec_0, 0))
        self.connect((self.lora_sdr_dewhitening_0, 0), (self.lora_sdr_crc_verif_0, 0))
        self.connect((self.lora_sdr_fft_demod_0, 0), (self.lora_sdr_gray_enc_0, 0))
        self.connect((self.lora_sdr_frame_sync_0, 0), (self.lora_sdr_fft_demod_0, 0))
        self.connect((self.lora_sdr_gray_enc_0, 0), (self.lora_sdr_deinterleaver_0, 0))
        self.connect((self.lora_sdr_hamming_dec_0, 0), (self.lora_sdr_header_decoder_0, 0))
        self.connect((self.lora_sdr_header_decoder_0, 0), (self.lora_sdr_dewhitening_0, 0))
        self.connect((self.uhd_usrp_source_0, 0), (self.interp_fir_filter_xxx_0, 0))
        self.connect((self.uhd_usrp_source_0, 0), (self.qtgui_freq_sink_x_0, 0))


    def closeEvent(self, event):
        self.settings = Qt.QSettings("GNU Radio", "lora_RX")
        self.settings.setValue("geometry", self.saveGeometry())
        self.stop()
        self.wait()

        event.accept()

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.set_bw(self.samp_rate)
        self.qtgui_freq_sink_x_0.set_frequency_range(self.center_freq, self.samp_rate)
        self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)

    def get_sf(self):
        return self.sf

    def set_sf(self, sf):
        self.sf = sf
        self._sf_callback(self.sf)

    def get_pay_len(self):
        return self.pay_len

    def set_pay_len(self, pay_len):
        self.pay_len = pay_len

    def get_impl_head(self):
        return self.impl_head

    def set_impl_head(self, impl_head):
        self.impl_head = impl_head
        self._impl_head_callback(self.impl_head)

    def get_has_crc(self):
        return self.has_crc

    def set_has_crc(self, has_crc):
        self.has_crc = has_crc
        self._has_crc_callback(self.has_crc)

    def get_cr(self):
        return self.cr

    def set_cr(self, cr):
        self.cr = cr
        self._cr_callback(self.cr)

    def get_center_freq(self):
        return self.center_freq

    def set_center_freq(self, center_freq):
        self.center_freq = center_freq
        self.qtgui_freq_sink_x_0.set_frequency_range(self.center_freq, self.samp_rate)
        self.uhd_usrp_source_0.set_center_freq(self.center_freq, 0)

    def get_bw(self):
        return self.bw

    def set_bw(self, bw):
        self.bw = bw
        self.uhd_usrp_source_0.set_bandwidth(self.bw, 1)




def main(top_block_cls=lora_RX, options=None):

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
