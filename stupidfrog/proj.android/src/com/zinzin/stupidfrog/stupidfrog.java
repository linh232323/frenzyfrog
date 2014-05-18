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
import org.json.JSONException;
import org.json.JSONObject;

import com.facebook.android.AsyncFacebookRunner;
import com.facebook.android.AsyncFacebookRunner.RequestListener;
import com.facebook.android.DialogError;
import com.facebook.android.Facebook;
import com.facebook.android.Facebook.DialogListener;
import com.facebook.android.FacebookError;

import android.content.Context;
import android.content.SharedPreferences;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.util.Log;

public class stupidfrog extends Cocos2dxActivity{
	
	private static String APP_FB_ID = "576695625778343"; // Replace your App ID here
	 // Instance of Facebook Class
    private  Facebook facebook;
    @SuppressWarnings("deprecation")
	private  AsyncFacebookRunner mAsyncRunner;
    String FILENAME = "AndroidSSO_data";
    private static SharedPreferences mPrefs;
    
    protected void onCreate(Bundle savedInstanceState){
    	
		super.onCreate(savedInstanceState);	
		
		facebook = new Facebook(APP_FB_ID);
        mAsyncRunner = new AsyncFacebookRunner(facebook);
        
        
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
    @SuppressWarnings("deprecation")
	public void postToWall() {
        // post on user's wall.
        facebook.dialog(this, "feed", new DialogListener() {
     
            @Override
            public void onFacebookError(FacebookError e) {
            }
     
            @Override
            public void onError(DialogError e) {
            }
     
            @Override
            public void onComplete(Bundle values) {
            }
     
            @Override
            public void onCancel() {
            }
        });
     
    }
    @SuppressWarnings("deprecation")
	public void loginToFacebook() {
        mPrefs = getPreferences(MODE_PRIVATE);
        String access_token = mPrefs.getString("access_token", null);
        long expires = mPrefs.getLong("access_expires", 0);
     
        if (access_token != null) {
            facebook.setAccessToken(access_token);
        }
     
        if (expires != 0) {
            facebook.setAccessExpires(expires);
        }
     
        if (!facebook.isSessionValid()) {
            facebook.authorize(this,
                    new String[] { "email", "publish_stream" },
                    new DialogListener() {
     
                        @Override
                        public void onCancel() {
                            // Function to handle cancel event
                        }
     
                        @SuppressWarnings("deprecation")
						@Override
                        public void onComplete(Bundle values) {
                            // Function to handle complete event
                            // Edit Preferences and update facebook acess_token
                            SharedPreferences.Editor editor = mPrefs.edit();
                            editor.putString("access_token",
                                    facebook.getAccessToken());
                            editor.putLong("access_expires",
                                    facebook.getAccessExpires());
                            editor.commit();
                        }
     
                        @Override
                        public void onError(DialogError error) {
                            // Function to handle error
     
                        }
     
                        @Override
                        public void onFacebookError(FacebookError fberror) {
                            // Function to handle Facebook errors
     
                        }
     
                    });
        }
    }
    
    @SuppressWarnings("deprecation")
	public void postFeed(){
    	// post on user's wall.
        facebook.dialog(this, "feed", new DialogListener() {
     
            @Override
            public void onFacebookError(FacebookError e) {
            }
     
            @Override
            public void onError(DialogError e) {
            }
     
            @Override
            public void onComplete(Bundle values) {
            }
     
            @Override
            public void onCancel() {
            }
        });
     
    }
   
}
