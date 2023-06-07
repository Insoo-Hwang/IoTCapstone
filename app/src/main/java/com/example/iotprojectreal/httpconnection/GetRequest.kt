package com.example.iotprojectreal.httpconnection

import android.app.Activity
import android.os.AsyncTask
import android.util.Log
import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.net.HttpURLConnection
import java.net.URL
import javax.net.ssl.HttpsURLConnection

abstract class GetRequest(protected var activity: Activity?) : AsyncTask<String?, Void?, String?>() {
    protected var url: URL? = null
    protected override fun doInBackground(vararg p0: String?): String? {
        val output = StringBuffer()
        try {
            if (url == null) {
                Log.e(TAG, "Error: URL is null ")
                return null
            }
            val conn = url!!.openConnection() as HttpURLConnection
            if (conn == null) {
                Log.e(TAG, "HttpsURLConnection Error")
                return null
            }
            conn.connectTimeout = 10000
            conn.requestMethod = "GET"
            conn.doInput = true
            conn.doOutput = false
            val resCode = conn.responseCode
            if (resCode != HttpsURLConnection.HTTP_OK) {
                Log.e(TAG, "HttpsURLConnection ResponseCode: $resCode")
                conn.disconnect()
                return null
            }
            val reader = BufferedReader(InputStreamReader(conn.inputStream))
            var line: String? = null
            while (true) {
                line = reader.readLine()
                if (line == null) {
                    break
                }
                output.append(line)
            }
            reader.close()
            conn.disconnect()
        } catch (ex: IOException) {
            Log.e(TAG, "Exception in processing response.", ex)
            ex.printStackTrace()
        }
        return output.toString()
    }

    companion object {
        const val TAG = "AndroidAPITest"
    }
}