基于MatrixPanel的signalRGB点阵屏幕，内置WiFiweb服务、udp、AP配网、仿WLED协议与signalRGB建立通讯，因为esp32s3的udp数据处理能力有限，特将signalRGB输出的数据进行压缩传送，使用此代码需要替换signalRGB的WLED.JS文件。
使用的是ESP32S3和40*80的点阵板
希望各位大神优化细节上的问题。




这是演示视频。
https://github.com/aokailin/signalRGB-/assets/110108894/470b2919-930f-4cf5-a61e-5089acbab8f1



这个是WLED.JS需要修改的地方：
		for(let CurrPacket = 0; CurrPacket <Math.ceil(NumPackets / 2); CurrPacket++) {
			const startIdx = CurrPacket * MaxLedsInPacket;
			const highByte = ((startIdx >> 8) & 0xFF);
			const lowByte = (startIdx & 0xFF);
			let packet = [0x04, 0x02, highByte, CurrPacket];
			let led1 = RGBData.splice(0, MaxLedsInPacket*3);
			let led2 = RGBData.splice(0, MaxLedsInPacket*3);
			let RGBTEMP = [ ];
			
			for (let i = 0; i < led1.length; i++) {
  			  // 将L1中的每个元素除以16，然后合并到L3中
    			const valueFromled1 = (led1[i] / 16) & 0xF;
    			RGBTEMP.push(valueFromled1);
			}

			for (let i = 0; i < led2.length; i++) {
    			// 将L2中的每个元素除以16，然后合并到L3中
    			const valueFromled2 = (led2[i] / 16) & 0xF;
    			RGBTEMP.push(valueFromled2);
			}
	
			packet = packet.concat(RGBTEMP.splice(0, MaxLedsInPacket*3));
			udp.send(this.ip, this.streamingPort, packet, BIG_ENDIAN);
		}
	}
