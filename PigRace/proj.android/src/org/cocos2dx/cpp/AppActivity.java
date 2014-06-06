/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
package org.cocos2dx.cpp;

import jp.co.septeni.pyxis.extralibrary.IGetAdIDComplete;
import jp.co.septeni.pyxis.extralibrary.PYXISExtraLibrary;
import jp.co.septeni.pyxisadmeasure.PYXISTracking;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;

public class AppActivity extends Cocos2dxActivity implements IGetAdIDComplete {

	private static final String ACTIVE_MV = "63ad9e2c07a5aac8724ca0b1342f9f20";
	private static final String PURCHASE_MV = "43f953ff2cf0ae7355aa0be01948bd9e";
	private static final String OTHER_MV = "167f1d284f093d4d015cb0447170531a";

	private PYXISExtraLibrary mPyxisExtraLibrary;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Initialize SDK.
		initSDK();

		mPyxisExtraLibrary = new PYXISExtraLibrary(this, this);
		mPyxisExtraLibrary.getAdvertisingID();
	}

	/**
	 * Initialize SDK.
	 */
	private void initSDK() {
		PYXISTracking.init(this, getIntent());

		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Track purchase event.
	 */
	public static void trackPurchase() {
		PYXISTracking.trackEvent(PURCHASE_MV, "", 20, 200, 2000, "");
	}

	public static void trackOthers() {
		PYXISTracking.trackEvent(OTHER_MV, "suidTesting", 10, 100, 1000, "otherTesting");
	}

	@Override
	public void onComplete(String id) {
		// Set device IDs.
		PYXISTracking.setExtraID(PYXISExtraLibrary.KEY_ADVERTISING_ID, id);
		PYXISTracking.setExtraID(PYXISExtraLibrary.KEY_ANDROID_ID, mPyxisExtraLibrary.getAndroidID());
		PYXISTracking.setExtraID(PYXISExtraLibrary.KEY_IMEI, mPyxisExtraLibrary.getIMEI());
		PYXISTracking.setExtraID(PYXISExtraLibrary.KEY_MAC_ADDRESS, mPyxisExtraLibrary.getMACAddress());
		
		// Track install event.
		PYXISTracking.trackInstall();
		// Track DAU.
		PYXISTracking.trackDau(ACTIVE_MV, "other_testing");
	}
}
