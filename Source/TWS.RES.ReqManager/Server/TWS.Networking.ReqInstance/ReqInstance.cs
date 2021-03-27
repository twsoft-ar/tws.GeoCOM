using System;
using System.Collections.Generic;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Runtime.InteropServices;
using System.Reflection;
using LOG = TWS.Log.Logger;
using static TWS.Log.Logger;

namespace TWS.Networking
{
    public class ReqInstance
    {
        private Socket mSocket;

        public ReqInstance(Socket socket_)
        {
            mSocket = socket_;
        }

        public virtual void StartProcess()
        {
            ReqMessage requestMsg = WaitForRequest();
            ReqMessage responseMsg;

            try
            {

                if (requestMsg.MessageType != MSG_DEF.INVALID_MSG)
                {
                    responseMsg = ProcessIncomingRequest(requestMsg);

                    if (!SendResponse(responseMsg))
                    {
                        #if(WindowsCE == false)
                        LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In StartProcess() error sending response message", VERBOSITY_LEVEL.FATAL);
                        #else
                        LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In StartProcess() error sending response message", VERBOSITY_LEVEL.FATAL);
                        #endif
                    }
                }

            }
            catch (Exception ex)
            {
                #if (WindowsCE == false)
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In StartProcess() Exception thrown: " + ex.Message, VERBOSITY_LEVEL.FATAL);
                #else
                LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In StartProcess() Exception thrown: " + ex.Message, VERBOSITY_LEVEL.FATAL);
                #endif
            }
            finally
            {
                mSocket.Close();
            }
        }

        public Socket Socket
        {
            get { return mSocket; }
            set { mSocket = value; }
        }

        protected ReqInstance()
        { }

        ReqMessage WaitForRequest()
        {
            ReqMessage retVal = new ReqMessage(null);

            const Int32 bufferSize = 8192;
            Int32 totalBytesRecv;
            Int32 bytesRecv;
            Byte[] buffer = new Byte[bufferSize];
            bool stopReceiving;
            Int32 elapsedTime;

            totalBytesRecv  = 0;
            elapsedTime     = 0;
            stopReceiving   = false;

            totalBytesRecv = 0;

            while (!stopReceiving)
            {
                try
                {
                    bytesRecv = 0;

                    while (!stopReceiving && bytesRecv >= 0)
                    {
                        bytesRecv = mSocket.Receive(buffer, totalBytesRecv, bufferSize - totalBytesRecv, SocketFlags.None);

                        if (bytesRecv > -1)
                            totalBytesRecv += bytesRecv;
                    }

                }
                catch (SocketException se)
                {                    
                    #if(WindowsCE == false)
                    if (se.ErrorCode != (int)SocketError.WouldBlock)
                    {
                        LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In WaitForRequest(), SocketException thrown: " + se.Message, VERBOSITY_LEVEL.FATAL);
                        break;
                    }
                    #else
                    if (se.ErrorCode != (int)10035)
                    {
                        LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In WaitForRequest(), SocketException thrown: " + se.Message, VERBOSITY_LEVEL.FATAL);
                        break;
                    }
                    #endif
                }
                catch (ObjectDisposedException ode)
                {
                    #if (WindowsCE == false)
                    LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In WaitForRequest(), ObjectDisposedException thrown: " + ode.Message, VERBOSITY_LEVEL.FATAL);
                    #else
                    LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In WaitForRequest(), ObjectDisposedException thrown: " + ode.Message, VERBOSITY_LEVEL.FATAL);
                    #endif

                    break;
                }

                if (totalBytesRecv > 0)
                {
                    retVal = ReqMessage.ReqMessageFromByteStream(buffer, ref totalBytesRecv);
                    stopReceiving = (retVal.MessageType != MSG_DEF.INVALID_MSG);
                }

                stopReceiving = stopReceiving || (elapsedTime > 5000);

                Thread.Sleep(10);
                elapsedTime += 10;
                        
            }//end while

            return retVal;
        }

        protected bool SendResponse(ReqMessage msg_)
        {
            bool retVal = false;
            
            Int32 bytesToSend = msg_.HeaderSize + msg_.BodySize;
            Int32 sentBytes = 0;
            Int32 totalSentBytes = 0;

            Byte[] buffer_ = msg_.ToPByte();

            try
            {
                while (totalSentBytes < bytesToSend && sentBytes >=0)
                {
                    sentBytes = mSocket.Send(buffer_, totalSentBytes, bytesToSend - totalSentBytes, SocketFlags.None);
                    totalSentBytes += sentBytes;
                }

                retVal = (totalSentBytes == bytesToSend);
            }
            catch (SocketException se)
            {
                #if(WindowsCE == false)
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In SendResponse(), SocketException thrown: " + se.Message, VERBOSITY_LEVEL.FATAL);
                #else
                LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In SendResponse(), SocketException thrown: " + se.Message, VERBOSITY_LEVEL.FATAL);
                #endif
            }
            catch (ObjectDisposedException ode)
            {
                #if(WindowsCE == false)
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In SendResponse(), ObjectDisposedException thrown: " + ode.Message, VERBOSITY_LEVEL.FATAL);
                #else
                LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In SendResponse(), ObjectDisposedException thrown: " + ode.Message, VERBOSITY_LEVEL.FATAL);
                #endif
            }
            catch (Exception ex)
            {
                #if(WindowsCE == false)
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In SendResponse(), Exception thrown: " + ex.Message, VERBOSITY_LEVEL.FATAL);
                #else
                LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", "In SendResponse(), Exception thrown: " + ex.Message, VERBOSITY_LEVEL.FATAL);
                #endif
            }

            return retVal;
        }
    
        protected virtual ReqMessage ProcessIncomingRequest(ReqMessage msg_)
        {
            ReqMessage retVal = new ReqMessage(null);

	        //this method is only executed if no ReqInstance derived class method is executed
	        //due to no existance of such derived class

	        string strMsg = "";

	        strMsg  =  "Message type->" + retVal.MessageType.ToString() + " received";
            #if(WindowsCE == false)
            LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", strMsg, VERBOSITY_LEVEL.INFO);
            #else
            LOG.Instance.LogEvent(Assembly.GetCallingAssembly().GetName().CodeBase + ".log", strMsg, VERBOSITY_LEVEL.INFO);
            #endif

	        strMsg = "Derived ReqInstance not implemented\0";

            retVal.MessageType = 0;
            retVal.Body = Marshaling.ByteStream.ToPByte(strMsg);
            retVal.BodySize = retVal.Body.Length;

            return retVal;
        }

        protected virtual string LogFileName
        {
            get 
            {
                #if(WindowsCE == false)
                return Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log";
                #else
                return Assembly.GetCallingAssembly().GetName().CodeBase + ".log";
                #endif
            }
        }
    }
}
