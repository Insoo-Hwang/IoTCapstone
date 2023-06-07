package com.example.iotprojectreal.ui

import android.graphics.Bitmap
import android.graphics.Color
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.amazonaws.mobile.client.AWSMobileClient
import com.amazonaws.mobile.client.Callback
import com.amazonaws.mobile.client.UserStateDetails
import com.example.iotprojectreal.databinding.ActivityListBinding
import com.google.zxing.BarcodeFormat
import com.google.zxing.EncodeHintType
import com.google.zxing.qrcode.QRCodeWriter
import com.google.zxing.qrcode.decoder.ErrorCorrectionLevel
import java.util.*


class ListActivity : AppCompatActivity() {
    lateinit var binding : ActivityListBinding
    override fun onCreate(savedInstanceState : Bundle?){
        super.onCreate(savedInstanceState)
        binding = ActivityListBinding.inflate(layoutInflater)
        setContentView(binding.root)


        //binding.button2.setOnClickListener {
            AWSMobileClient.getInstance().initialize(
                applicationContext,
                object : Callback<UserStateDetails?> {
                    override fun onResult(userStateDetails: UserStateDetails?) {
                        val sub = AWSMobileClient.getInstance().userAttributes.get("sub").toString()
                        System.out.println(sub)
                        System.out.println("####################")
                        binding.imageView.setImageBitmap(generateQRCode(sub))
                    }

                    override fun onError(e: Exception) {}
                })
        //}

    }

    fun generateQRCode(text: String): Bitmap {
        val hints = Hashtable<EncodeHintType, Any>()
        hints[EncodeHintType.CHARACTER_SET] = "UTF-8"
        hints[EncodeHintType.ERROR_CORRECTION] = ErrorCorrectionLevel.H
        val qrCodeWriter = QRCodeWriter()
        val bitMatrix = qrCodeWriter.encode(text, BarcodeFormat.QR_CODE, 512, 512, hints)

        val bitmap = Bitmap.createBitmap(512, 512, Bitmap.Config.ARGB_8888)
        for (x in 0 until 512) {
            for (y in 0 until 512) {
                bitmap.setPixel(x, y, if (bitMatrix[x, y]) Color.BLACK else Color.WHITE)
            }
        }

        return bitmap
    }
}