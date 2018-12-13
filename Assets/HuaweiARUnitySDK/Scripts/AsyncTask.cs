//-----------------------------------------------------------------------
// <copyright file="AsyncTask.cs" company="Google">
//
// Copyright 2017 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// </copyright>
//-----------------------------------------------------------------------
namespace HuaweiARUnitySDK
{
    using System;
    using System.Collections.Generic;
    using UnityEngine;
    using HuaweiARInternal;

    public class AsyncTask<T>
    {
        private List<Action<T>> actionListAfterTaskCompletion;
        public T TaskResult { get; private set; }
        public bool IsTaskCompleted { get; private set; }

        public AsyncTask(T result)
        {
            TaskResult = result;
            IsTaskCompleted = true;
        }

        public AsyncTask(out Action<T> asyncPerformActionAfterTaskCompleted)
        {
            IsTaskCompleted = false;
            asyncPerformActionAfterTaskCompleted = delegate (T result)
            {
                TaskResult = result;
                IsTaskCompleted = true;
                if (actionListAfterTaskCompletion != null)
                {
                    AsyncTask.AddTask(() =>
                    {
                        for (int i = 0; i < actionListAfterTaskCompletion.Count; i++)
                        {
                            actionListAfterTaskCompletion[i](result);
                        }
                    });
                }
            };
        }

        public CustomYieldInstruction GetWaitForCompletionYieldInstruction()
        {
            return new WaitForAsynTaskCompletionYieldInstruction<T>(this);
        }

        public AsyncTask<T> ThenAction(Action<T> actionAfterTask)
        {
            if (IsTaskCompleted)
            {
                actionAfterTask(TaskResult);
                return this;
            }

            if (actionListAfterTaskCompletion == null)
            {
                actionListAfterTaskCompletion = new List<Action<T>>();
            }

            actionListAfterTaskCompletion.Add(actionAfterTask);
            return this;
        }
    }


    public class AsyncTask
    {
        private static Queue<Action> actionQueue = new Queue<Action>();

        private static object for_lock = new object();

        public static void AddTask(Action action)
        {
            lock (for_lock)
            {
                actionQueue.Enqueue(action);
            }
        }

        public static void Update()
        {
            lock (for_lock)
            {
                while (actionQueue.Count > 0)
                {
                    actionQueue.Dequeue().Invoke();
                }
            }
        }
    }
}
