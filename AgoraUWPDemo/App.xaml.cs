using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace AgoraUWPDemo
{
    /// <summary>
    /// Provide application-specific behavior to supplement the default application classes.
    /// </summary>
    sealed partial class App : Application
    {
        /// <summary>
        ////// Initialize the singleton application object. This is the first line of the authoring code executed,
        /// Has been executed, logically equivalent to main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;
        }

        /// <summary>
        /// Called when the application is normally launched by the end user.
        /// Will be used when starting an application to open a specific file, etc.

        /// </summary>
        /// <param name="e"> Detailed information about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {
            Frame rootFrame = Window.Current.Content as Frame;

            // Do not repeat the application initialization when the window already contains content,
            // Just make sure the window is active

            if (rootFrame == null)
            {
                // Create a frame to act as a navigation context and navigate to the first page
                rootFrame = new Frame();

                rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: Load the state from the previously suspended application
                }

                // put the frame in the current window
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame.Content == null)
                {
                  // When the navigation stack has not been restored, navigate to the first page,
                  // and configure by passing the required information as navigation parameters
                  // parameters
                    rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }
                // Make sure the current window is active
                Window.Current.Activate();
            }
        }

        /// <summary>
        /// Called when navigation to a specific page fails
        /// </summary>
        ///<param name="sender">Navigation failure frame</param>
        ///<param name="e">Details about navigation failure</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// Called when the application execution is about to be suspended. Not knowing the application
        /// No need to know whether the application will be terminated or restored,
        /// And keep the memory content unchanged.
        /// </summary>
          /// <param name="sender">The source of the pending request.</param>
        /// <param name="e">Details about the pending request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }
    }
}
