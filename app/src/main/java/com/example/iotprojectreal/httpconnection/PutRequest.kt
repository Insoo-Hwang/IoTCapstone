package com.example.iotprojectreal.httpconnection

import android.app.Activity
import android.os.AsyncTask
import android.util.Log
import org.json.JSONObject
import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.lang.Exception
import java.net.HttpURLConnection
import java.net.URL
import javax.net.ssl.HttpsURLConnection

open class PutRequest(protected var activity: Activity?) : AsyncTask<JSONObject?, Void?, String?>() {
    protected var url: URL? = null
    protected override fun doInBackground(vararg p0: JSONObject?): String? {
        try {
            val conn = url!!.openConnection() as HttpURLConnection
            conn.readTimeout = 10000
            conn.connectTimeout = 10000
            conn.requestMethod = "PUT"
            conn.setRequestProperty("Content-type", "application/json")
            conn.doInput = true
            conn.doOutput = true
            val os = conn.outputStream
            val writer = BufferedWriter(
                OutputStreamWriter(os, "UTF-8")
            )
            val str = p0[0].toString()
            Log.e("params", "Post String = $str")
            writer.write(str)
            writer.flush()
            writer.close()
            os.close()
            val responseCode = conn.responseCode
            return if (responseCode == HttpsURLConnection.HTTP_OK) {
                val `in` = BufferedReader(InputStreamReader(conn.inputStream))
                val sb = StringBuffer("")
                var line: String? = ""
                while (`in`.readLine().also { line = it } != null) {
                    sb.append(line)
                    break
                }
                `in`.close()
                sb.toString()
            } else {
                String("Server Error : $responseCode".toByteArray())
            }
        } catch (e: Exception) {
            e.printStackTrace()
        }
        return null
    }
}