/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.zinzin.stupidfrog;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.text.TextUtils;

public class stupidfrog extends Cocos2dxActivity{
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
	}

    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// stupidfrog should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }
    public static String getDeviceUniqueId() {
		TelephonyManager telephonyManager = (TelephonyManager)getContext().getSystemService(Context.TELEPHONY_SERVICE);
		if (telephonyManager != null
				&& !TextUtils.isEmpty(telephonyManager.getDeviceId())) {
			return telephonyManager.getDeviceId();
		}
		WifiManager wifiMan = (WifiManager) getContext().getSystemService(Context.WIFI_SERVICE);
		WifiInfo wifiInf = wifiMan.getConnectionInfo();
		System.out.println("MAC" + wifiInf.getMacAddress());
		if(wifiInf.getMacAddress() == "")
			return "1";
		return wifiInf.getMacAddress();
	}
	
	
    	// get device name
    public static  String getDeviceName() 
    {
		String manufacturer = Build.MANUFACTURER;
		String model = Build.MODEL;
		if (model.startsWith(manufacturer)) 
		{
			return capitalize(model);
		}
		else 
		{
			return capitalize(manufacturer) + " " + model;
		}
	}		 	
	public static boolean checkNetworkConnectivity()
	{
		ConnectivityManager conMgr = (ConnectivityManager)getContext().getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo i = conMgr.getActiveNetworkInfo();
		if (i == null || !i.isConnected() || !i.isAvailable())
		{
		    return false;
		}
		return true;
	}
	private static  String capitalize(String s) {
			if (s == null || s.length() == 0) {
				return "";
			}
			char first = s.charAt(0);
			if (Character.isUpperCase(first)) {
				return s;
			} else {
				return Character.toUpperCase(first) + s.substring(1);
			}
	}
    static {
        System.loadLibrary("cocos2dcpp");
    }     
}
